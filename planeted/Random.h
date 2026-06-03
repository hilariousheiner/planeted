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

        void SetNumberOfOctaves(std::uint32_t numberOfOctaves);
        void SetPersistence(float persistence);
        void SetLacunarity(float lacunarity);

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

        float FBM1D(const float &p, NoiseFunction1D noiseFun);
        float FBM2D(const Vector2 &p, NoiseFunction2D noiseFun);
        float FBM3D(const Vector3 &p, NoiseFunction3D noiseFun);

        inline NoiseFunction1D Billow1D(NoiseFunction1D noiseFun)
        {
            return [noiseFun](const float &p)
            {
                return std::abs(noiseFun(p));
            };
        }
        inline NoiseFunction2D Billow2D(NoiseFunction2D noiseFun)
        {
            return [noiseFun](const Vector2 &p)
            {
                return std::abs(noiseFun(p));
            };
        }
        inline NoiseFunction3D Billow3D(NoiseFunction3D noiseFun)
        {
            return [noiseFun](const Vector3 &p)
            {
                return std::abs(noiseFun(p));
            };
        }

        inline NoiseFunction1D Ridge1D(NoiseFunction1D noiseFun)
        {
            return [noiseFun](const float &p)
            {
                float n = (0.9f - std::abs(noiseFun(p)));
                return n*n;
            };
        }
        inline NoiseFunction2D Ridge2D(NoiseFunction2D noiseFun)
        {
            return [noiseFun](const Vector2 &p)
            {
                float n = (0.9f - std::abs(noiseFun(p)));
                return n*n;
            };
        }
        inline NoiseFunction3D Ridge3D(NoiseFunction3D noiseFun)
        {
            return [noiseFun](const Vector3 &p)
            {
                float n = (0.9f - std::abs(noiseFun(p)));
                return n*n;
            };
        }
    }
}
#endif // PLANETED_RANDOM_H
