#include "Random.h"

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

            float u0 = SmoothStepUnclamped(c00, c10, tx);
            float u1 = SmoothStepUnclamped(c01, c11, tx);

            return SmoothStepUnclamped(u0, u1, ty);
        }

        static float GetValue(const Vector3 &p)
        {
            // calculate grid cell corner coordinates:
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);
            int zi = FloorToInt(p.Z);

            int x0 = ValueNoise::toGrid(xi);
            int y0 = ValueNoise::toGrid(yi);
            int z0 = ValueNoise::toGrid(zi);

            int x1 = ValueNoise::toGrid(x0 + 1);
            int y1 = ValueNoise::toGrid(y0 + 1);
            int z1 = ValueNoise::toGrid(z0 + 1);

            // get noise value at cell corners:
            const float &c000 = ValueNoise::randomValue(x0, y0, z0);
            const float &c100 = ValueNoise::randomValue(x1, y0, z0);
            const float &c010 = ValueNoise::randomValue(x0, y1, z0);
            const float &c110 = ValueNoise::randomValue(x1, y1, z0);

            const float &c001 = ValueNoise::randomValue(x0, y0, z1);
            const float &c101 = ValueNoise::randomValue(x1, y0, z1);
            const float &c011 = ValueNoise::randomValue(x0, y1, z1);
            const float &c111 = ValueNoise::randomValue(x1, y1, z1);

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

        static const float &randomValue(const int &x, const int &y, const int &z)
        {
            return ValueNoise::valueTable()[ValueNoise::permute(x, y, z)];
        }

        static unsigned int permute(const int &x)
        {
            return ValueNoise::permutationTable()[x];
        }

        static unsigned int permute(const int &x, const int &y)
        {
            return ValueNoise::permutationTable()[ValueNoise::permutationTable()[x] + y];
        }

        static unsigned int permute(const int &x, const int &y, const int &z)
        {
            return ValueNoise::permutationTable()[ValueNoise::permutationTable()[ValueNoise::permutationTable()[x] + y] + z];
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

        float ValueNoise(const float &p)
        {
            return ValueNoise::GetValue(p);
        }
        float ValueNoise(const Vector2 &p)
        {
            return ValueNoise::GetValue(p);
        }
        float ValueNoise(const Vector3 &p)
        {
            return ValueNoise::GetValue(p);
        }

        float FBM(const Vector3 &p)
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
