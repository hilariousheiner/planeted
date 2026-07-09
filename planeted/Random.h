#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <algorithm>
#include <array>
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

        enum class NoiseStyleEnum
        {
            Plain = 0,
            Billow = 1,
            Ridge = 2
        };

        struct FBMParameters
        {
            FBMParameters();

            std::uint32_t NumberOfOctaves;
            float Lacunarity;
            float Persistence;
            float StartFrequency;
            bool Normalize;
            float Exponent;
        };

        void SeedNoise(std::uint32_t seed);
        void SeedNoise(std::string seed);

        struct NoiseParameters
        {
            NoiseParameters();

            std::uint32_t seed;

            float WhiteNoiseScale;
        };

        using NoiseFunction1D = std::function<float(const float&, const NoiseParameters&)>;
        using NoiseFunction2D = std::function<float(const Vector2 &p, const NoiseParameters&)>;
        using NoiseFunction3D = std::function<float(const Vector3 &p, const NoiseParameters&)>;

        NoiseFunction1D GetNoiseFunction1D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle);
        NoiseFunction2D GetNoiseFunction2D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle);
        NoiseFunction3D GetNoiseFunction3D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle);

        float WhiteNoise1D(const float &p, const NoiseParameters &params);
        float WhiteNoise2D(const Vector2 &p, const NoiseParameters &params);
        float WhiteNoise3D(const Vector3 &p, const NoiseParameters &params);

        float ValueNoise1D(const float &p, const NoiseParameters &params);
        float ValueNoise2D(const Vector2 &p, const NoiseParameters &params);
        float ValueNoise3D(const Vector3 &p, const NoiseParameters &params);

        float PerlinNoise1D(const float &p, const NoiseParameters &params);
        float PerlinNoise2D(const Vector2 &p, const NoiseParameters &params);
        float PerlinNoise3D(const Vector3 &p, const NoiseParameters &params);

        NoiseFunction1D GetBaseNoiseFunction1D(NoiseTypeEnum noiseType);
        NoiseFunction2D GetBaseNoiseFunction2D(NoiseTypeEnum noiseType);
        NoiseFunction3D GetBaseNoiseFunction3D(NoiseTypeEnum noiseType);

        float FBM1D(const float &p, const FBMParameters &fbmParams, const NoiseParameters &noiseParams, NoiseFunction1D noiseFun);
        float FBM2D(const Vector2 &p, const FBMParameters &fbmParams, const NoiseParameters &noiseParams, NoiseFunction2D noiseFun);
        float FBM3D(const Vector3 &p, const FBMParameters &fbmParams, const NoiseParameters &noiseParams, NoiseFunction3D noiseFun);

        using NoiseTransform1D = std::function<NoiseFunction1D(NoiseFunction1D)>;
        using NoiseTransform2D = std::function<NoiseFunction2D(NoiseFunction2D)>;
        using NoiseTransform3D = std::function<NoiseFunction3D(NoiseFunction3D)>;

        NoiseFunction1D Billow1D(NoiseFunction1D noiseFun);
        NoiseFunction2D Billow2D(NoiseFunction2D noiseFun);
        NoiseFunction3D Billow3D(NoiseFunction3D noiseFun);

        NoiseFunction1D Ridge1D(NoiseFunction1D noiseFun);
        NoiseFunction2D Ridge2D(NoiseFunction2D noiseFun);
        NoiseFunction3D Ridge3D(NoiseFunction3D noiseFun);

        NoiseTransform1D GetNoiseStyleTransform1D(NoiseStyleEnum noiseStyle);
        NoiseTransform2D GetNoiseStyleTransform2D(NoiseStyleEnum noiseStyle);
        NoiseTransform3D GetNoiseStyleTransform3D(NoiseStyleEnum noiseStyle);
    }
}
#endif // PLANETED_RANDOM_H
