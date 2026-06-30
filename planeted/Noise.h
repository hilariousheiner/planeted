#ifndef PLANETED_NOISE_H
#define PLANETED_NOISE_H

#include "Random.h"

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
}
#endif
