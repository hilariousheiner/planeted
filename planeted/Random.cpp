#include "Random.h"

namespace Planeted
{
    void Random::Seed(uint32_t seed)
    {
        Random::engine() = std::mt19937(seed);
    }

    float Random::Range(float min, float max)
    {
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(Random::engine());
    }

    std::mt19937& Random::engine()
    {
        static std::mt19937 en(std::random_device{}());
        return en;
    }
}
