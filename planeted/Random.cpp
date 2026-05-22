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

        static const float randomDotGrad(const std::uint8_t &x, const float tx)
        {
            return permute(x) & 1 ? tx : -tx;
        }

        static float randomDotGrad(const int &x, const int &y, const float tx, const float ty)
        {
            float result;

            switch(permute(x, y) & 7)
            {
            case 0:
                result = tx; // (1, 0) * (tx, ty)
            case 1:
                result = -tx; // (-1, 0) * (tx, ty)
                break;
            case 2:
                result = ty; // (0, 1) * (tx, ty)
                break;
            case 3:
                result = -ty; // (0, -1) * (tx, ty)
                break;
            case 4:
                result = tx + ty; // (1, 1) * (tx, ty)
                break;
            case 5:
                result = -tx + ty; // (-1, 1) * (tx, ty)
                break;
            case 6:
                result = tx - ty; // (1, -1) * (tx, ty)
                break;
            case 7:
                result = -tx - ty; // (-1, -1) * (tx, ty)
                break;
            default:
                break;
            }
            return result;
        }

        static float randomDotGrad(const int &x, const int &y, const int &z, const float tx, const float ty, const float tz)
        {
            float result;

            switch(permute(x,y,z) & 15)
            {
            case 0:
                result = tx + ty; //(1,1,0) * (tx, ty, tz)
                break;
            case 1:
                result = -tx + ty; //(-1,1,0) * (tx, ty, tz)
                break;
            case 2:
                result = tx - ty;  //(1,-1,0) * (tx, ty, tz)
                break;
            case 3:
                result = -tx - ty;//(-1,-1,0) * (tx, ty, tz)
                break;
            case 4:
                result = tx + tz; //(1,0,1) * (tx, ty, tz)
                break;
            case 5:
                result = -tx + tz; //(-1,0,1) * (tx, ty, tz)
                break;
            case 6:
                result = tx - tz; //(1,0,-1) * (tx, ty, tz)
                break;
            case 7:
                result = -tx - tz;//(-1,0,-1) * (tx, ty, tz)
                break;
            case 8:
                result = ty + tz; //(0,1,1) * (tx, ty, tz)
                break;
            case 9:
                result = -ty + tz; //(0,-1,1) * (tx, ty, tz)
                break;
            case 10:
                result = ty - tz; //(0,1,-1) * (tx, ty, tz)
                break;
            case 11:
                result = -ty - tz; //(0,-1,-1) * (tx, ty, tz)
                break;
            case 12:
                result = tx + ty; //(1,1,0) * (tx, ty, tz)
                break;
            case 13:
                result = -tx + ty; //(-1,1,0) * (tx, ty, tz)
                break;
            case 14:
                result = -ty + tz; //(0,-1,1) * (tx, ty, tz)
                break;
            case 15:
                result = -ty - tz; //(0,-1,-1) * (tx, ty, tz)
                break;
            }
            return result;
        }

        void SeedNoise(std::uint32_t seed)
        {
            noise_engine() = std::mt19937(seed);
            valueTable() = computeValueTable();
            permutationTable() = computePermutationTable();
        }

        float WhiteNoise(const float &p)
        {
            int pi = std::floor(p);

            uint32_t h = hash1D(pi, 12345);

            return hashToSigned(h);
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

        float GradientNoise(const float &p)
        {
            int pi = FloorToInt(p);

            std::uint8_t p0 = toGrid(pi);
            std::uint8_t p1 = toGrid(p0 + 1);

            float tp = p - pi;

            const float g0 = randomDotGrad(p0, tp);
            const float g1 = randomDotGrad(p1, tp - 1);

            return SmoothStepUnclamped5(g0, g1, tp);
        }

        float WhiteNoise(const Vector2 &p)
        {
            int xi = std::floor(p.X);
            int yi = std::floor(p.Y);

            uint32_t h = hash2D(xi, yi, 12345);

            return hashToSigned(h);
        }

        float ValueNoise(const Vector2 &p)
        {
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);

            int xi0 = toGrid(xi);
            int yi0 = toGrid(yi);

            int xi1 = toGrid(xi0 + 1);
            int yi1 = toGrid(yi0 + 1);

            float tx = p.X - xi;
            float ty = p.Y - yi;

            const float &c00 = randomValue(xi0, yi0);
            const float &c10 = randomValue(xi1, yi0);
            const float &c01 = randomValue(xi0, yi1);
            const float &c11 = randomValue(xi1, yi1);

            float u0 = SmoothStepUnclamped(c00, c10, tx);
            float u1 = SmoothStepUnclamped(c01, c11, tx);

            return SmoothStepUnclamped(u0, u1, ty);
        }

        float GradientNoise(const Vector2 &p)
        {
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);

            int xi0 = toGrid(xi);
            int yi0 = toGrid(yi);

            int xi1 = toGrid(xi0 + 1);
            int yi1 = toGrid(yi0 + 1);

            float tx = p.X - xi;
            float ty = p.Y - yi;

            const float &c00 = randomDotGrad(xi0, yi0, tx, ty);
            const float &c10 = randomDotGrad(xi1, yi0, tx - 1, ty);
            const float &c01 = randomDotGrad(xi0, yi1, tx, ty - 1);
            const float &c11 = randomDotGrad(xi1, yi1, tx - 1, ty - 1);

            float u0 = SmoothStepUnclamped5(c00, c10, tx);
            float u1 = SmoothStepUnclamped5(c01, c11, tx);

            return SmoothStepUnclamped5(u0, u1, ty);
        }

        float WhiteNoise(const Vector3 &p)
        {
            int xi = std::floor(p.X);
            int yi = std::floor(p.Y);
            int zi = std::floor(p.Z);

            uint32_t h = hash3D(xi, yi, zi, 12345);

            return hashToSigned(h);
        }

        float ValueNoise(const Vector3 &p)
        {
             // calculate grid cell corner coordinates:
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);
            int zi = FloorToInt(p.Z);

            int xi0 = toGrid(xi);
            int yi0 = toGrid(yi);
            int zi0 = toGrid(zi);

            int xi1 = toGrid(xi0 + 1);
            int yi1 = toGrid(yi0 + 1);
            int zi1 = toGrid(zi0 + 1);

            float tx = p.X - xi;
            float ty = p.Y - yi;
            float tz = p.Z - zi;

            // get noise value at cell corners:
            const float &c000 = randomValue(xi0, yi0, zi0);
            const float &c100 = randomValue(xi1, yi0, zi0);
            const float &c010 = randomValue(xi0, yi1, zi0);
            const float &c110 = randomValue(xi1, yi1, zi0);

            const float &c001 = randomValue(xi0, yi0, zi1);
            const float &c101 = randomValue(xi1, yi0, zi1);
            const float &c011 = randomValue(xi0, yi1, zi1);
            const float &c111 = randomValue(xi1, yi1, zi1);

            // interpolate:
            float u00 = SmoothStepUnclamped(c000, c100, tx);
            float u10 = SmoothStepUnclamped(c010, c110, tx);

            float u01 = SmoothStepUnclamped(c001, c101, tx);
            float u11 = SmoothStepUnclamped(c011, c111, tx);

            float v0 = SmoothStepUnclamped(u00, u10, ty);
            float v1 = SmoothStepUnclamped(u01, u11, ty);

            return SmoothStepUnclamped(v0, v1, tz);
        }

        float GradientNoise(const Vector3 &p)
        {
             // calculate grid cell corner coordinates:
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);
            int zi = FloorToInt(p.Z);

            int xi0 = toGrid(xi);
            int yi0 = toGrid(yi);
            int zi0 = toGrid(zi);

            int xi1 = toGrid(xi0 + 1);
            int yi1 = toGrid(yi0 + 1);
            int zi1 = toGrid(zi0 + 1);

            float tx = p.X - xi;
            float ty = p.Y - yi;
            float tz = p.Z - zi;

            // compute dot products with gradients at cell corners:
            const float &c000 = randomDotGrad(xi0, yi0, zi0, tx    , ty    , tz   );
            const float &c100 = randomDotGrad(xi1, yi0, zi0, tx - 1, ty    , tz   );
            const float &c010 = randomDotGrad(xi0, yi1, zi0, tx    , ty - 1, tz   );
            const float &c110 = randomDotGrad(xi1, yi1, zi0, tx - 1, ty - 1, tz   );

            const float &c001 = randomDotGrad(xi0, yi0, zi1, tx    , ty    , tz - 1);
            const float &c101 = randomDotGrad(xi1, yi0, zi1, tx - 1, ty    , tz - 1);
            const float &c011 = randomDotGrad(xi0, yi1, zi1, tx    , ty - 1, tz - 1);
            const float &c111 = randomDotGrad(xi1, yi1, zi1, tx - 1, ty - 1, tz - 1);

            // interpolate:
            float u00 = SmoothStepUnclamped5(c000, c100, tx);
            float u10 = SmoothStepUnclamped5(c010, c110, tx);

            float u01 = SmoothStepUnclamped5(c001, c101, tx);
            float u11 = SmoothStepUnclamped5(c011, c111, tx);

            float v0 = SmoothStepUnclamped5(u00, u10, ty);
            float v1 = SmoothStepUnclamped5(u01, u11, ty);

            return SmoothStepUnclamped5(v0, v1, tz);
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


        float GradientNoiseFBM(const Vector3 &p)
        {
            float G = 0.5f;
            float f = 1.0f;
            float a = 1.0f;
            float t = 0.0f;

            for(int i = 0; i < 4; ++i)
            {
                t += a*GradientNoise(p*f);

                f *= 2.0f;
                a *= G;
            }
            return t;
        }
    }
}
