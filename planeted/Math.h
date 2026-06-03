#ifndef PLANETED_MATH_H
#define PLANETED_MATH_H

#include <cmath>
#include <cstdint>
#include <string>

namespace Planeted
{
    template <typename T>
    inline T Clamp(const T &value, const T &minVal, const T &maxVal)
    {
        return std::max(minVal, std::min(maxVal, value));
    }

    template <typename T>
    inline T Clamp01(const T &value)
    {
        return Clamp(value, static_cast<T>(0), static_cast<T>(1));
    }

    template <typename T, typename U>
    inline T Lerp(const T &a, const T &b, const U &t)
    {
        return a + (b - a) * Clamp01(t);
    }

    template <typename T, typename U>
    inline T LerpUnclamped(const T &a, const T &b, const U &t)
    {
        return a + (b - a) * t;
    }

    template <typename T, typename U>
    inline T SmoothStep(const T &a, const T &b, const U &t)
    {
        U x = Clamp01(t);
        x = x * x * (static_cast<U>(3) - static_cast<U>(2) * x);
        return LerpUnclamped(a, b, x);
    }

    template <typename T, typename U>
    inline T SmoothStepUnclamped(const T &a, const T &b, const U &t)
    {
        U x = t * t * (static_cast<U>(3) - static_cast<U>(2) * t);
        return LerpUnclamped(a, b, x);
    }

    template <typename T, typename U>
    inline T SmoothStepUnclamped5(const T &a, const T &b, const U &t)
    {
        U x = t * t * t * (t * (t * static_cast<U>(6) - static_cast<U>(15)) + static_cast<U>(10));
        return LerpUnclamped(a, b, x);
    }

    inline int FloorToInt(const float &value)
    {
        int i = static_cast<int>(value);
        return (value < 0 && value != i) ? i - 1 : i;
    }

    inline std::uint8_t ToUint8(float x)
    {
        x = Clamp01(x);
        return static_cast<std::uint8_t>(std::round(x * 255.0f));
    }

    // maps[-1, 1] to [0, 1]
    inline float SignedToUnitRange(float x)
    {
        x = std::max(-1.0f, std::min(1.0f, x));
        return (x + 1.0f) * 0.5f;
    }

    // murmurhash finalizer, written by Austin Appleby:
    // https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
    inline uint32_t FMix32(uint32_t h)
    {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }

    // 64 bit version of musmurhash finalizer, written by Autin Appleby:
    // https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
    inline uint64_t FMix64(uint64_t k)
    {
        k ^= k >> 33;
        k *= 0xff51afd7ed558ccdULL;
        k ^= k >> 33;
        k *= 0xc4ceb9fe1a85ec53ULL;
        k ^= k >> 33;

        return k;
    }

    inline uint32_t Hash1D(int x, uint32_t seed)
    {
        uint32_t h = seed;

        h ^= uint32_t(x) * 0x9e3779b1;

        return FMix32(h);
    }

    inline uint32_t Hash2D(int x, int y, uint32_t seed)
    {
        uint32_t h = seed;

        h ^= uint32_t(x) * 0x9e3779b1;
        h ^= uint32_t(y) * 0x85ebca77;

        return FMix32(h);
    }

    inline uint32_t Hash3D(int x, int y, int z, uint32_t seed)
    {
        uint32_t h = seed;

        h ^= uint32_t(x) * 0x9e3779b1;
        h ^= uint32_t(y) * 0x85ebca77;
        h ^= uint32_t(z) * 0xc2b2ae3d;

        return FMix32(h);
    }

    inline float HashToSigned(uint32_t h)
    {
        float u = h * (1.0 / 4294967296.0);
        return u * 2.0 - 1.0;
    }

    // FNV-1a hash function:
    // https://en.wikipedia.org/wiki/Fowler-Noll-Vo_hash_function
    inline uint32_t FNV32(const std::string &s)
    {
        uint32_t h = 2166136261u; //FNV offset basis

        for (unsigned char c : s)
        {
            h ^= static_cast<uint32_t>(c);
            h *= 16777619u; //FNV prime
        }
        return h;
    }
    inline uint64_t FNV64(const std::string& text)
    {
        uint64_t h = 14695981039346656037ull;

        for (unsigned char c : text)
        {
            h ^= static_cast<uint64_t>(c);
            h *= 1099511628211ull;
        }
        return h;
    }

    inline uint32_t StringToSeed32(const std::string &s)
    {
        return FMix32(FNV32(s));
    }
    inline uint32_t StringToSeed64(const std::string &s)
    {
        return FMix64(FNV64(s));
    }

    // SplitMix64 by Sebastiano Vigna
    // https://prng.di.unimi.it/splitmix64.c
    inline uint64_t SplitMix64(uint64_t &state)
    {
        state += 0x9e3779b97f4a7c15ull;

        uint64_t z = state;

        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ull;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebull;

        return z ^ (z >> 31);
    }

    constexpr int PermutationSize = 256;

    using Permutation = std::array<uint8_t, PermutationSize>;
    using PermutationTable = std::array<uint8_t, PermutationSize * 2>;

    inline PermutationTable MakePermutationTable(Permutation &permutation, uint64_t seed)
    {
        PermutationTable result;

        // copy the permutation into the first half of the table:
        for (int i = 0; i < PermutationSize; ++i)
        {
            result[i] = permutation[i];
        }

        // shuffle the first half of the table
        // using a Fisher-Yates shuffle with SplitMix64:
        uint64_t state = seed;

        for (int i = PermutationSize-1; i > 0; --i)
        {
            int j = static_cast<int>(SplitMix64(state) % (i + 1));
            std::swap(result[i], result[j]);
        }

        // duplicate the shuffled permutation into the second half of the table:
        for (int i = 0; i < PermutationSize; ++i)
        {
            result[i + PermutationSize] = result[i];
        }

        // done.
        return result;
    }
}
#endif // PLANETED_MATH_H
