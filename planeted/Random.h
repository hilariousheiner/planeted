#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <random>

namespace Planeted
{
    class Random
    {
    public:
        static void Seed(uint32_t seed);
        static float Range(float min, float max);
    private:
        static std::mt19937& engine();
    };
}
#endif // PLANETED_RANDOM_H
