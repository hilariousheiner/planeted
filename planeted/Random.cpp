#include "Random.h"

namespace Planeted
{
    namespace Random
    {
        static std::mt19937& engine()
        {
            static std::mt19937 en(std::random_device{}());
            return en;
        }

        void Seed(uint32_t seed)
        {
            engine() = std::mt19937(seed);
        }

        float Range(float min, float max)
        {
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(engine());
        }
    }
}
