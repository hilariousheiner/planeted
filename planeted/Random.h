#ifndef PLANETED_RANDOM_H
#define PLANETED_RANDOM_H

#include <random>

namespace Planeted
{
    class Random
    {
    public:
        static void Seed(uint32_t seed)
        {
            Random::engine() = std::mt19937(seed);
        }

        static float Range(float min, float max)
        {
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(Random::engine());
        }

    private:
        static std::mt19937& engine()
        {
            static std::mt19937 en(std::random_device{}());
            return en;
        }
    };
}
#endif // PLANETED_RANDOM_H
