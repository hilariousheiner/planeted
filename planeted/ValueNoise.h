#ifndef PLANETED_VALUENOISE_H
#define PLANETED_VALUENOISE_H

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <random>

#include "Math.h"

namespace Planeted
{
    class ValueNoise
    {
    public:
        static float GetValue(const float &p)
        {
            int pi = FloorToInt(p);

            int p0 = pi & (ValueNoise::tableSize - 1);
            int p1 = (p0 + 1) & (ValueNoise::tableSize - 1);

            const float &c0 = ValueNoise::valueTable()[p0];
            const float &c1 = ValueNoise::valueTable()[p1];

            return SmoothStepUnclamped(c0, c1, p - pi);
        }

        static float GetValue(const Vector2 &p)
        {
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);

            int x0 = xi & (ValueNoise::tableSize - 1);
            int x1 = (x0 + 1) & (ValueNoise::tableSize - 1);
            int y0 = yi & (ValueNoise::tableSize - 1);
            int y1 = (y0 + 1) & (ValueNoise::tableSize - 1);

            const float &c00 = ValueNoise::valueTable()[ValueNoise::permute(x0, y0)];
            const float &c10 = ValueNoise::valueTable()[ValueNoise::permute(x1, y0)];
            const float &c01 = ValueNoise::valueTable()[ValueNoise::permute(x0, y1)];
            const float &c11 = ValueNoise::valueTable()[ValueNoise::permute(x1, y1)];

            float s0 = SmoothStepUnclamped(c00, c10, p.X - xi);
            float s1 = SmoothStepUnclamped(c01, c11, p.X - xi);

            return SmoothStepUnclamped(s0, s1, p.Y - yi);
        }

    private:
        static const unsigned int tableSize = 256;

        static unsigned int permute(const int &p)
        {
            return ValueNoise::permutationTable()[p];
        }

        static unsigned int permute(const int &x, const int &y)
        {
            return ValueNoise::permutationTable()[ValueNoise::permutationTable()[x] + y];
        }

        static std::array<float, ValueNoise::tableSize>& valueTable()
        {
            static std::array<float, ValueNoise::tableSize> result = []
            {
                std::array<float, ValueNoise::tableSize> tmp;

                std::mt19937 engine(std::random_device{}());
                std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

                // create an array of random values
                for (float &entry : tmp)
                {
                    entry = distribution(engine);
                }
                return tmp;
            }();
            return result;
        }

        static std::array<unsigned int, ValueNoise::tableSize * 2>& permutationTable()
        {
            static std::array<unsigned int, ValueNoise::tableSize * 2> result = []
            {
                std::array<unsigned int, ValueNoise::tableSize *2> tmp;

                unsigned int i = 0;
                for(unsigned int &entry : tmp)
                {
                    entry = i;
                    ++i;
                }

                std::mt19937 engine(std::random_device{}());

                std::shuffle(tmp.begin(), tmp.end(), engine);

                return tmp;
            }();
            return result;
        }
    };
}
#endif // PLANETED_VALUENOISE_H
