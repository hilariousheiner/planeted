#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <algorithm>
#include <array>
#include <cmath> //for std::abs
#include <functional>
#include <string>

#include "Math.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Planeted
{
    namespace Random
    {
        enum class NoiseTypeEnum
        {
            White = 0,
            Value = 1,
            Perlin = 2,
            Gradient = 3
        };

        using NoiseFunction1D = std::function<float(const float&)>;
        using NoiseFunction2D = std::function<float(const Vector2 &p)>;
        using NoiseFunction3D = std::function<float(const Vector3 &p)>;

        void SeedNoise(std::uint32_t seed);
        void SeedNoise(std::string seed);

        void SetWhiteNoiseScale(float scale);

        float WhiteNoise1D(const float &p);
        float WhiteNoise2D(const Vector2 &p);
        float WhiteNoise3D(const Vector3 &p);

        float ValueNoise1D(const float &p);
        float ValueNoise2D(const Vector2 &p);
        float ValueNoise3D(const Vector3 &p);

        float PerlinNoise1D(const float &p);
        float PerlinNoise2D(const Vector2 &p);
        float PerlinNoise3D(const Vector3 &p);

        NoiseFunction1D GetBaseNoiseFunction1D(NoiseTypeEnum noiseType);
        NoiseFunction2D GetBaseNoiseFunction2D(NoiseTypeEnum noiseType);
        NoiseFunction3D GetBaseNoiseFunction3D(NoiseTypeEnum noiseType);

        void SetNumberOfOctaves(std::uint32_t numberOfOctaves);
        void SetStartFrequency(float frequency);
        void SetLacunarity(float lacunarity);
        void SetPersistence(float persistence);

        float FBM1D(const float &p, NoiseFunction1D noiseFun);
        float FBM2D(const Vector2 &p, NoiseFunction2D noiseFun);
        float FBM3D(const Vector3 &p, NoiseFunction3D noiseFun);

        enum class NoiseStyleEnum
        {
            Plain = 0,
            Billow = 1,
            Ridge = 2
        };

        using NoiseTransform1D = std::function<NoiseFunction1D(NoiseFunction1D)>;
        using NoiseTransform2D = std::function<NoiseFunction2D(NoiseFunction2D)>;
        using NoiseTransform3D = std::function<NoiseFunction3D(NoiseFunction3D)>;

        NoiseFunction1D Billow1D(NoiseFunction1D noiseFun);
        NoiseFunction2D Billow2D(NoiseFunction2D noiseFun);
        NoiseFunction3D Billow3D(NoiseFunction3D noiseFun);

        NoiseFunction1D Ridge1D(NoiseFunction1D noiseFun);
        NoiseFunction2D Ridge2D(NoiseFunction2D noiseFun);
        NoiseFunction3D Ridge3D(NoiseFunction3D noiseFun);

        inline NoiseTransform1D GetNoiseStyleTransform1D(NoiseStyleEnum noiseStyle)
        {
            NoiseTransform1D result = nullptr;

            switch(noiseStyle)
            {
            case NoiseStyleEnum::Plain:
                break;
            case NoiseStyleEnum::Billow:
                result = Billow1D;
                break;
            case NoiseStyleEnum::Ridge:
                result = Ridge1D;
                break;
            default:
                break;
            }
            return result;
        }
        inline NoiseTransform2D GetNoiseStyleTransform2D(NoiseStyleEnum noiseStyle)
        {
            NoiseTransform2D result = nullptr;

            switch(noiseStyle)
            {
            case NoiseStyleEnum::Plain:
                break;
            case NoiseStyleEnum::Billow:
                result = Billow2D;
                break;
            case NoiseStyleEnum::Ridge:
                result = Ridge2D;
                break;
            default:
                break;
            }
            return result;
        }
        inline NoiseTransform3D GetNoiseStyleTransform3D(NoiseStyleEnum noiseStyle)
        {
            NoiseTransform3D result = nullptr;

            switch(noiseStyle)
            {
            case NoiseStyleEnum::Plain:
                break;
            case NoiseStyleEnum::Billow:
                result = Billow3D;
                break;
            case NoiseStyleEnum::Ridge:
                result = Ridge3D;
                break;
            default:
                break;
            }
            return result;
        }

        inline NoiseFunction1D GetNoiseFunction1D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle)
        {
            NoiseFunction1D result = GetBaseNoiseFunction1D(noiseType);
            NoiseTransform1D noiseTransform = GetNoiseStyleTransform1D(noiseStyle);

            if(noiseTransform != nullptr)
            {
                result = noiseTransform(result);
            }
            return result;
        }
        inline NoiseFunction2D GetNoiseFunction2D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle)
        {
            NoiseFunction2D result = GetBaseNoiseFunction2D(noiseType);
            NoiseTransform2D noiseTransform = GetNoiseStyleTransform2D(noiseStyle);

            if(noiseTransform != nullptr)
            {
                result = noiseTransform(result);
            }
            return result;
        }
        inline NoiseFunction3D GetNoiseFunction3D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle)
        {
            NoiseFunction3D result = GetBaseNoiseFunction3D(noiseType);
            NoiseTransform3D noiseTransform = GetNoiseStyleTransform3D(noiseStyle);

            if(noiseTransform != nullptr)
            {
                result = noiseTransform(result);
            }
            return result;
        }
    }
}
#endif // PLANETED_RANDOM_H
