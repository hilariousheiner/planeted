#ifndef PLANETED_NOISE_H
#define PLANETED_NOISE_H

#include "Random.h"

namespace Planeted
{
    class Noise
    {
    public:
        Noise();

        void SetNumberOfOctaves(std::uint32_t numberOfOctaves);
        void SetStartFrequency(float startFrequency);
        void SetLacunarity(float lacunarity);
        void SetPersistence(float persistence);
        void SetNormalizeFBM(bool normalize);
        void SetExponent(float exponent);

        void SetWhiteNoiseScale(float scale);

        float Noise1D(const float &p) const;
        float Noise2D(const Vector2 &p) const;
        float Noise3D(const Vector3 &p) const;

        Random::NoiseTypeEnum noiseType;
        Random::NoiseStyleEnum noiseStyle;

        Random::NoiseParameters noiseParams;
        Random::FBMParameters fbmParams;
    };
}
#endif
