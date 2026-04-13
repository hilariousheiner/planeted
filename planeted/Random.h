#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <random>

#include "Vector3.h"

namespace Planeted
{
    namespace Random
    {
        void Seed(uint32_t seed);
        float Range(float min, float max);

        float FBM(const Vector3 &p);
    }
}
#endif // PLANETED_RANDOM_H
