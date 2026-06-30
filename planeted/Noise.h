#ifndef PLANETED_NOISE_H
#define PLANETED_NOISE_H

#include "Random.h"
#include "PRNG.h"

namespace Planeted
{
    class Noise
    {
        public:
        Noise();
        Noise(std::string seed);
        Noise(std::uint32_t seed);

        float Noise1D(const float &p) const;
        float Noise2D(const Vector2 &p) const;
        float Noise3D(const Vector3 &p) const;

        Random::NoiseTypeEnum noiseType;
        Random::NoiseStyleEnum noiseStyle;

        Random::NoiseParameters noiseParams;
        Random::FBMParameters fbmParams;

    private:
        std::uint32_t seed;
        std::uint64_t seed64;
    };

    Noise::Noise()
    {
        this->seed = StringToSeed32("Planeted");
        this->seed64 = StringToSeed64("Planeted");
    }
    Noise::Noise(std::string seed)
    {
        this->seed = StringToSeed32(seed);
        this->seed64 = StringToSeed64(seed);
    }
    Noise::Noise(std::uint32_t seed)
    {
        this->seed = seed;
        this->seed64 = FMix64(static_cast<uint64_t>(seed));
    };

    float Noise::Noise1D(const float &p) const
    {
        return Random::FBM1D(p, this->fbmParams, this->noiseParams, Random::GetNoiseFunction1D(this->noiseType, this->noiseStyle));
    }
    float Noise::Noise2D(const Vector2 &p) const
    {
        return Random::FBM2D(p, this->fbmParams, this->noiseParams, Random::GetNoiseFunction2D(this->noiseType, this->noiseStyle));
    }
    float Noise::Noise3D(const Vector3 &p) const
    {
        return Random::FBM3D(p, this->fbmParams, this->noiseParams, Random::GetNoiseFunction3D(this->noiseType, this->noiseStyle));
    }
}
#endif
