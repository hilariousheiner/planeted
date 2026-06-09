#include "PRNG.h"

namespace Planeted
{
    uint32_t FMix32(uint32_t h)
    {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }
    uint64_t FMix64(uint64_t k)
    {
        k ^= k >> 33;
        k *= 0xff51afd7ed558ccdULL;
        k ^= k >> 33;
        k *= 0xc4ceb9fe1a85ec53ULL;
        k ^= k >> 33;

        return k;
    }

    uint32_t Hash1D(int x, uint32_t seed)
    {
        uint32_t h = seed;

        h ^= uint32_t(x) * 0x9e3779b1;

        return FMix32(h);
    }
    uint32_t Hash2D(int x, int y, uint32_t seed)
    {
        uint32_t h = seed;

        h ^= uint32_t(x) * 0x9e3779b1;
        h ^= uint32_t(y) * 0x85ebca77;

        return FMix32(h);
    }
    uint32_t Hash3D(int x, int y, int z, uint32_t seed)
    {
        uint32_t h = seed;

        h ^= uint32_t(x) * 0x9e3779b1;
        h ^= uint32_t(y) * 0x85ebca77;
        h ^= uint32_t(z) * 0xc2b2ae3d;

        return FMix32(h);
    }

    uint64_t SplitMix64(uint64_t &state)
    {
        state += 0x9e3779b97f4a7c15ull;

        uint64_t z = state;

        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ull;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebull;

        return z ^ (z >> 31);
    }

    uint32_t FNV32(const std::string &s)
    {
        uint32_t h = 2166136261u; //FNV offset basis

        for (unsigned char c : s)
        {
            h ^= static_cast<uint32_t>(c);
            h *= 16777619u; //FNV prime
        }
        return h;
    }
    uint64_t FNV64(const std::string &s)
    {
        uint64_t h = 14695981039346656037ull;

        for (unsigned char c : s)
        {
            h ^= static_cast<uint64_t>(c);
            h *= 1099511628211ull;
        }
        return h;
    }

    float HashToSigned(uint32_t h)
    {
        float u = h * (1.0 / 4294967296.0);
        return u * 2.0 - 1.0;
    }
    uint32_t StringToSeed32(const std::string &s)
    {
        return FMix32(FNV32(s));
    }
    uint32_t StringToSeed64(const std::string &s)
    {
        return FMix64(FNV64(s));
    }

    PermutationTable MakePermutationTable(Permutation &permutation, uint64_t seed)
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
