#ifndef PLANETED_PRNG_H
#define PLANETED_PRNG_H

#include <array>
#include <cmath>
#include <cstdint>
#include <string>

namespace Planeted
{
    // MurmuHash finalizers, written by Austin Appleby:
    // https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
    uint32_t FMix32(uint32_t h);
    uint64_t FMix64(uint64_t k);

    // coordinate hash functions:
    uint32_t Hash1D(int x, uint32_t seed);
    uint32_t Hash2D(int x, int y, uint32_t seed);
    uint32_t Hash3D(int x, int y, int z, uint32_t seed);

    // SplitMix64 by Sebastiano Vigna
    // https://prng.di.unimi.it/splitmix64.c
    uint64_t SplitMix64(uint64_t &state);

    // FNV-1a hash functions:
    // https://en.wikipedia.org/wiki/Fowler-Noll-Vo_hash_function
    uint32_t FNV32(const std::string &s);
    uint64_t FNV64(const std::string &s);

    // Utils:
    float HashToSigned(uint32_t h);
    uint32_t StringToSeed32(const std::string &s);
    uint32_t StringToSeed64(const std::string &s);


    // Permutation tables:
    constexpr int PermutationSize = 256;

    using Permutation = std::array<uint8_t, PermutationSize>;
    using PermutationTable = std::array<uint8_t, PermutationSize * 2>;

    PermutationTable MakePermutationTable(Permutation &permutation, uint64_t seed);
}
#endif // PLANETED_PRNG_H
