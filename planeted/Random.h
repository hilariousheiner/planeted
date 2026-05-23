#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <algorithm>
#include <array>
#include <functional>

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

        float WhiteNoise1D(const float &p);
        float WhiteNoise2D(const Vector2 &p);
        float WhiteNoise3D(const Vector3 &p);

        float ValueNoise1D(const float &p);
        float ValueNoise2D(const Vector2 &p);
        float ValueNoise3D(const Vector3 &p);

        float GradientNoise1D(const float &p);
        float GradientNoise2D(const Vector2 &p);
        float GradientNoise3D(const Vector3 &p);

        float FBM1D(const float &p, NoiseFunction1D noiseFun);
        float FBM2D(const Vector2 &p, NoiseFunction2D noiseFun);
        float FBM3D(const Vector3 &p, NoiseFunction3D noiseFun);
    }
}
#endif // PLANETED_RANDOM_H
