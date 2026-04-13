#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <random>

namespace Planeted
{
    namespace Random
    {
        void Seed(uint32_t seed);
        float Range(float min, float max);
    }
}
#endif // PLANETED_RANDOM_H
