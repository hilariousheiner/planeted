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

        void SetNumberOfOctaves(std::uint32_t numberOfOctaves);
        void SetStartFrequency(float startFrequency);
        void SetLacunarity(float lacunarity);
        void SetPersistence(float persistence);
        void SetNormalizeFBM(bool normalize);

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
