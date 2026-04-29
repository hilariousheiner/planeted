#include "Random.h"

namespace Planeted
{
    namespace Random
    {
        static const std::uint16_t valueNoiseTableSize = 256;

        static std::mt19937 &engine()
        {
            static std::mt19937 en(std::random_device{}());
            return en;
        }

        static std::mt19937 &noise_engine()
        {
            static std::mt19937 en(std::random_device{}());
            return en;
        }

        static std::array<float, valueNoiseTableSize> computeValueTable()
        {
            std::array<float, valueNoiseTableSize> result;

            std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

            // create an array of random values
            for (float &entry : result)
            {
                entry = distribution(noise_engine());
            }
            return result;
        }

        static std::array<std::uint8_t, valueNoiseTableSize * 2> computePermutationTable()
        {
            std::array<std::uint8_t, valueNoiseTableSize * 2> result;

            for(std::size_t i = 0; i < valueNoiseTableSize; ++i)
            {
                result[i] = i;
                result[i + valueNoiseTableSize] = i;
            }

            std::shuffle(result.begin(), result.end(), noise_engine());

            return result;
        }
        static std::array<std::uint8_t, valueNoiseTableSize * 2> &permutationTable()
        {
            static std::array<std::uint8_t, valueNoiseTableSize * 2> result = computePermutationTable();
            return result;
        }

        static std::array<float, valueNoiseTableSize> &valueTable()
        {
            static std::array<float, valueNoiseTableSize> result = computeValueTable();
            return result;
        }

        static std::uint8_t toGrid(const int &x)
        {
            return static_cast<std::uint8_t>(x & (valueNoiseTableSize - 1));
        }

        static std::uint8_t permute(const std::uint8_t &x)
        {
            return permutationTable()[x];
        }

        static std::uint8_t permute(const int &x, const int &y)
        {
            return permutationTable()[permutationTable()[x] + y];
        }

        static std::uint8_t permute(const int &x, const int &y, const int &z)
        {
            return permutationTable()[permutationTable()[permutationTable()[x] + y] + z];
        }

        static const float &randomValue(const int &x)
        {
            return valueTable()[permute(x)];
        }

        static const float &randomValue(const int &x, const int &y)
        {
            return valueTable()[permute(x, y)];
        }

        static const float &randomValue(const int &x, const int &y, const int &z)
        {
            return valueTable()[permute(x, y, z)];
        }

        void Seed(std::uint32_t seed)
        {
            engine() = std::mt19937(seed);
        }

        void SeedValueNoise(std::uint32_t seed)
        {
            noise_engine() = std::mt19937(seed);
            valueTable() = computeValueTable();
            permutationTable() = computePermutationTable();
        }

        float Range(float min, float max)
        {
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(engine());
        }

        float ValueNoise(const float &p)
        {
            int pi = FloorToInt(p);

            std::uint8_t p0 = toGrid(pi);
            std::uint8_t p1 = toGrid(p0 + 1);

            const float &c0 = randomValue(p0);
            const float &c1 = randomValue(p1);

            return SmoothStepUnclamped(c0, c1, p - pi);
        }

        float ValueNoise(const Vector2 &p)
        {
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);

            int x0 = toGrid(xi);
            int y0 = toGrid(yi);

            int x1 = toGrid(x0 + 1);
            int y1 = toGrid(y0 + 1);

            const float &c00 = randomValue(x0, y0);
            const float &c10 = randomValue(x1, y0);
            const float &c01 = randomValue(x0, y1);
            const float &c11 = randomValue(x1, y1);

            float tx = p.X - xi;
            float ty = p.Y - yi;

            float u0 = SmoothStepUnclamped(c00, c10, tx);
            float u1 = SmoothStepUnclamped(c01, c11, tx);

            return SmoothStepUnclamped(u0, u1, ty);
        }

        float ValueNoise(const Vector3 &p)
        {
             // calculate grid cell corner coordinates:
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);
            int zi = FloorToInt(p.Z);

            int x0 = toGrid(xi);
            int y0 = toGrid(yi);
            int z0 = toGrid(zi);

            int x1 = toGrid(x0 + 1);
            int y1 = toGrid(y0 + 1);
            int z1 = toGrid(z0 + 1);

            // get noise value at cell corners:
            const float &c000 = randomValue(x0, y0, z0);
            const float &c100 = randomValue(x1, y0, z0);
            const float &c010 = randomValue(x0, y1, z0);
            const float &c110 = randomValue(x1, y1, z0);

            const float &c001 = randomValue(x0, y0, z1);
            const float &c101 = randomValue(x1, y0, z1);
            const float &c011 = randomValue(x0, y1, z1);
            const float &c111 = randomValue(x1, y1, z1);

            // interpolate:
            float tx = p.X - xi;
            float ty = p.Y - yi;
            float tz = p.Z - zi;

            float u00 = SmoothStepUnclamped(c000, c100, tx);
            float u10 = SmoothStepUnclamped(c010, c110, tx);

            float u01 = SmoothStepUnclamped(c001, c101, tx);
            float u11 = SmoothStepUnclamped(c011, c111, tx);

            float v0 = SmoothStepUnclamped(u00, u10, ty);
            float v1 = SmoothStepUnclamped(u01, u11, ty);

            return SmoothStepUnclamped(v0, v1, tz);
        }

        float ValueNoiseFBM(const float &p)
        {
            float G = 0.5f;
            float f = 1.0f;
            float a = 1.0f;
            float t = 0.0f;

            for(int i = 0; i < 4; ++i)
            {
                t += a*ValueNoise(p*f);

                f *= 2.0f;
                a *= G;
            }
            return t;
        }

        float ValueNoiseFBM(const Vector2 &p)
        {
            float G = 0.5f;
            float f = 1.0f;
            float a = 1.0f;
            float t = 0.0f;

            for(int i = 0; i < 4; ++i)
            {
                t += a*ValueNoise(p*f);

                f *= 2.0f;
                a *= G;
            }
            return t;
        }

        float ValueNoiseFBM(const Vector3 &p)
        {
            float G = 0.5f;
            float f = 1.0f;
            float a = 1.0f;
            float t = 0.0f;

            for(int i = 0; i < 4; ++i)
            {
                t += a*ValueNoise(p*f);

                f *= 2.0f;
                a *= G;
            }
            return t;
        }
    }
}
