#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <algorithm>
#include <array>
#include <random>

#include "Math.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Planeted
{
    namespace Random
    {
        void Seed(std::uint32_t seed);

        float Range(float min, float max);

        void SeedNoise(std::uint32_t seed);

        float ValueNoise(const float &p);
        float ValueNoise(const Vector2 &p);
        float ValueNoise(const Vector3 &p);

        float ValueNoiseFBM(const float &p);
        float ValueNoiseFBM(const Vector2 &p);
        float ValueNoiseFBM(const Vector3 &p);

        float GradientNoise(const float &p);
        float GradientNoise(const Vector2 &p);
        float GradientNoise(const Vector3 &p);

        float GradientNoiseFBM(const Vector3 &p);
    }
}
#endif // PLANETED_RANDOM_H
