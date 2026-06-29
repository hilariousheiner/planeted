#ifndef PLANETED_NOISE_H
#define PLANETED_NOISE_H

#include "Random.h"
#include "PRNG.h"

namespace Planeted
{
    class Noise3D
    {
        public:
        Noise3D();
        Noise3D(std::string seed);
        Noise3D(std::uint32_t seed);

        float Noise(const Vector3 &p) const;
    private:
        std::uint32_t seed;
        std::uint64_t seed64;

        Random::NoiseTypeEnum noiseType;
        Random::NoiseStyleEnum noiseStyle;

        Random::NoiseParameters noiseParams;
        Random::FBMParameters fbmParams;
    };

    Noise3D::Noise3D()
    {
        this->seed = StringToSeed32("Planeted");
        this->seed64 = StringToSeed64("Planeted");
    }
    Noise3D::Noise3D(std::string seed)
    {
        this->seed = StringToSeed32(seed);
        this->seed64 = StringToSeed64(seed);
    }
    Noise3D::Noise3D(std::uint32_t seed)
    {
        this->seed = seed;
        this->seed64 = FMix64(static_cast<uint64_t>(seed));
    };

    float Noise3D::Noise(const Vector3 &p) const
    {
        return Random::FBM3D(p, this->fbmParams, this->noiseParams, Random::GetNoiseFunction3D(this->noiseType, this->noiseStyle));
    }
}
#endif
