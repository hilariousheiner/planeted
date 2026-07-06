#include "Noise.h"
#include "PRNG.h"

namespace Planeted
{
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

    void Noise::SetNumberOfOctaves(std::uint32_t numberOfOctaves)
    {
        this->fbmParams.NumberOfOctaves = numberOfOctaves;
    }

    void Noise::SetStartFrequency(float startFrequency)
    {
        this->fbmParams.StartFrequency = startFrequency;
    }

    void Noise::SetLacunarity(float lacunarity)
    {
        this->fbmParams.Lacunarity = lacunarity;
    }

    void Noise::SetPersistence(float persistence)
    {
        this->fbmParams.Persistence = persistence;
    }

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
