#include "Random.h"
#include "ValueNoise.h"

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

        float FBM(const Vector3 &p)
        {
            float G = 0.5f;
            float f = 1.0f;
            float a = 1.0f;
            float t = 0.0f;

            for(int i = 0; i < 4; ++i)
            {
                t += a*ValueNoise::GetValue(p*f);

                f *= 2.0f;
                a *= G;
            }
            return t;
        }
    }
}
