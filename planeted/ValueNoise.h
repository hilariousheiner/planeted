#ifndef PLANETED_VALUENOISE_H
#define PLANETED_VALUENOISE_H

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <random>

#include "Math.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Planeted
{
    class ValueNoise
    {
    public:
        static float GetValue(const float &p)
        {
            int pi = FloorToInt(p);

            int p0 = ValueNoise::toGrid(pi);
            int p1 = ValueNoise::toGrid(p0 + 1);

            const float &c0 = ValueNoise::randomValue(p0);
            const float &c1 = ValueNoise::randomValue(p1);

            return SmoothStepUnclamped(c0, c1, p - pi);
        }

        static float GetValue(const Vector2 &p)
        {
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);

            int x0 = ValueNoise::toGrid(xi);
            int y0 = ValueNoise::toGrid(yi);

            int x1 = ValueNoise::toGrid(x0 + 1);
            int y1 = ValueNoise::toGrid(y0 + 1);

            const float &c00 = ValueNoise::randomValue(x0, y0);
            const float &c10 = ValueNoise::randomValue(x1, y0);
            const float &c01 = ValueNoise::randomValue(x0, y1);
            const float &c11 = ValueNoise::randomValue(x1, y1);

            float tx = p.X - xi;
            float ty = p.Y - yi;

            float s0 = SmoothStepUnclamped(c00, c10, tx);
            float s1 = SmoothStepUnclamped(c01, c11, tx);

            return SmoothStepUnclamped(s0, s1, ty);
        }

    private:

        static int toGrid(const int &x)
        {
            return x & (ValueNoise::tableSize - 1);
        }

        static const float &randomValue(const int &x)
        {
            return ValueNoise::valueTable()[ValueNoise::permute(x)];
        }

        static const float &randomValue(const int &x, const int &y)
        {
            return ValueNoise::valueTable()[ValueNoise::permute(x, y)];
        }

        static unsigned int permute(const int &x)
        {
            return ValueNoise::permutationTable()[x];
        }

        static unsigned int permute(const int &x, const int &y)
        {
            return ValueNoise::permutationTable()[ValueNoise::permutationTable()[x] + y];
        }

        static const unsigned int tableSize = 256;

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

                for(unsigned int i = 0; i < ValueNoise::tableSize; ++i)
                {
                    tmp[i] = i;
                    tmp[i + ValueNoise::tableSize] = i;
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
