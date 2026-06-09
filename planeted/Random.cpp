#include "Random.h"

#include <cmath> //for std::abs and std::pow

#include "PRNG.h"

namespace Planeted
{
    namespace Random
    {
        FBMParameters::FBMParameters()
        {
            this->NumberOfOctaves = 1;
            this->Lacunarity = 2.0f;
            this->Persistence = 0.5f;
            this->StartFrequency = 1.0f;
            this->Normalize = false;
            this->Exponent = 1.0f;
        }

        static std::uint32_t seed = StringToSeed32("Planeted");
        static std::uint64_t seed64 = StringToSeed64("Planeted");

        static std::uint32_t numberOfOctaves = 1;
        static float lacunarity = 2.0f;
        static float persistence = 0.5f;
        static float startFrequency = 1.0f;
        static bool normalizeFBM = false;
        static float exponent = 1.0f;

        static float whiteNoiseScale = 100.0f;

        static Permutation permutation =
        {
            8  , 170, 242, 67 , 248, 216, 115, 247, 164, 133, 195, 73 , 45 , 209, 13 , 53 ,
            9  , 131, 102, 214, 153, 254, 224, 63 , 244, 51 , 7  , 172, 106, 137, 95 , 201,
            41 , 71 , 166, 186, 83 , 197, 96 , 89 , 175, 226, 129, 34 , 80 , 97 , 93 , 12 ,
            84 , 70 , 152, 22 , 134, 125, 210, 135, 139, 49 , 100, 105, 109, 165, 117, 228,
            37 , 107, 11 , 24 , 128, 239, 86 , 88 , 108, 28 , 120, 76 , 98 , 19 , 118, 221,
            1  , 218, 82 , 179, 64 , 94 , 44 , 141, 149, 168, 99 , 187, 46 , 123, 243, 167,
            50 , 143, 85 , 193, 25 , 62 , 56 , 203, 200, 198, 26 , 119, 65 , 146, 246, 145,
            191, 15 , 91 , 233, 206, 176, 148, 48 , 78 , 27 , 35 , 101, 184, 87 , 207, 180,
            177, 23 , 81 , 219, 124, 55 , 250, 42 , 196, 59 , 5  , 161, 38 , 114, 230, 150,
            156, 10 , 240, 112, 31 , 162, 241, 213, 160, 238, 69 , 18 , 32 , 144, 151, 116,
            223, 234, 211, 154, 140, 127, 6  , 194, 122, 79 , 113, 75 , 217, 192, 163, 58 ,
            14 , 92 , 251, 190, 54 , 188, 227, 77 , 103, 181, 3  , 132, 208, 155, 253, 121,
            255, 60 , 245, 202, 157, 130, 52 , 36 , 173, 169, 74 , 29 , 39 , 4  , 17 , 147,
            47 , 61 , 252, 204, 159, 232, 225, 229, 57 , 43 , 237, 142, 183, 104, 72 , 236,
            2  , 189, 66 , 111, 30 , 158, 215, 126, 138, 220, 231, 249, 16 , 20 , 0  , 33 ,
            212, 182, 136, 185, 110, 40 , 235, 21 , 222, 178, 174, 205, 68 , 90 , 171, 199
        };

        static PermutationTable &permutationTable()
        {
            static PermutationTable result = MakePermutationTable(Random::permutation, Random::seed64);
            return result;
        }

        static std::uint8_t toGrid(const int &x)
        {
            return static_cast<std::uint8_t>(x & (PermutationSize - 1));
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

        static const float randomDotGradPerlin(const std::uint8_t &x, const float tx)
        {
            return permute(x) & 1 ? tx : -tx;
        }

        static float randomDotGradPerlin(const int &x, const int &y, const float tx, const float ty)
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

        static float randomDotGradPerlin(const int &x, const int &y, const int &z, const float tx, const float ty, const float tz)
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

        NoiseFunction1D GetNoiseFunction1D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle)
        {
            NoiseFunction1D result = GetBaseNoiseFunction1D(noiseType);
            NoiseTransform1D noiseTransform = GetNoiseStyleTransform1D(noiseStyle);

            if(noiseTransform != nullptr)
            {
                result = noiseTransform(result);
            }
            return result;
        }
        NoiseFunction2D GetNoiseFunction2D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle)
        {
            NoiseFunction2D result = GetBaseNoiseFunction2D(noiseType);
            NoiseTransform2D noiseTransform = GetNoiseStyleTransform2D(noiseStyle);

            if(noiseTransform != nullptr)
            {
                result = noiseTransform(result);
            }
            return result;
        }
        NoiseFunction3D GetNoiseFunction3D(NoiseTypeEnum noiseType, NoiseStyleEnum noiseStyle)
        {
            NoiseFunction3D result = GetBaseNoiseFunction3D(noiseType);
            NoiseTransform3D noiseTransform = GetNoiseStyleTransform3D(noiseStyle);

            if(noiseTransform != nullptr)
            {
                result = noiseTransform(result);
            }
            return result;
        }

        void SeedNoise(std::uint32_t seed)
        {
            Random::seed = seed;
            Random::seed64 = FMix64(static_cast<uint64_t>(seed));
        }
        void SeedNoise(std::string seed)
        {
            Random::seed = StringToSeed32(seed);
            Random::seed64 = StringToSeed64(seed);
        }

        void ResetNoise()
        {
            Random::numberOfOctaves = 1;
            Random::lacunarity = 2.0f;
            Random::persistence = 0.5f;
            Random::startFrequency = 1.0f;
            Random::normalizeFBM = false;
            Random::exponent = 1.0f;

            Random::whiteNoiseScale = 100.0f;
        }

        void SetWhiteNoiseScale(float scale)
        {
            Random::whiteNoiseScale = scale;
        }

        float WhiteNoise1D(const float &p)
        {
            int pi = std::floor(p * Random::whiteNoiseScale);

            uint32_t h = Hash1D(pi, Random::seed);

            return HashToSigned(h);
        }
        float WhiteNoise2D(const Vector2 &p)
        {
            int xi = std::floor(p.X * Random::whiteNoiseScale);
            int yi = std::floor(p.Y * Random::whiteNoiseScale);

            uint32_t h = Hash2D(xi, yi, Random::seed);

            return HashToSigned(h);
        }
        float WhiteNoise3D(const Vector3 &p)
        {
            int xi = std::floor(p.X * Random::whiteNoiseScale);
            int yi = std::floor(p.Y * Random::whiteNoiseScale);
            int zi = std::floor(p.Z * Random::whiteNoiseScale);

            uint32_t h = Hash3D(xi, yi, zi, Random::seed);

            return HashToSigned(h);
        }

        float ValueNoise1D(const float &p)
        {
            int pi = FloorToInt(p);

            std::uint8_t p0 = toGrid(pi);
            std::uint8_t p1 = toGrid(p0 + 1);

            const float &c0 = HashToSigned(Hash1D(p0, Random::seed));
            const float &c1 = HashToSigned(Hash1D(p1, Random::seed));

            return SmoothStepUnclamped(c0, c1, p - pi);
        }
        float ValueNoise2D(const Vector2 &p)
        {
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);

            int xi0 = toGrid(xi);
            int yi0 = toGrid(yi);

            int xi1 = toGrid(xi0 + 1);
            int yi1 = toGrid(yi0 + 1);

            float tx = p.X - xi;
            float ty = p.Y - yi;

            const float &c00 = HashToSigned(Hash2D(xi0, yi0, Random::seed));
            const float &c10 = HashToSigned(Hash2D(xi1, yi0, Random::seed));
            const float &c01 = HashToSigned(Hash2D(xi0, yi1, Random::seed));
            const float &c11 = HashToSigned(Hash2D(xi1, yi1, Random::seed));

            float u0 = SmoothStepUnclamped(c00, c10, tx);
            float u1 = SmoothStepUnclamped(c01, c11, tx);

            return SmoothStepUnclamped(u0, u1, ty);
        }
        float ValueNoise3D(const Vector3 &p)
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
            const float &c000 = HashToSigned(Hash3D(xi0, yi0, zi0, Random::seed));
            const float &c100 = HashToSigned(Hash3D(xi1, yi0, zi0, Random::seed));
            const float &c010 = HashToSigned(Hash3D(xi0, yi1, zi0, Random::seed));
            const float &c110 = HashToSigned(Hash3D(xi1, yi1, zi0, Random::seed));

            const float &c001 = HashToSigned(Hash3D(xi0, yi0, zi1, Random::seed));
            const float &c101 = HashToSigned(Hash3D(xi1, yi0, zi1, Random::seed));
            const float &c011 = HashToSigned(Hash3D(xi0, yi1, zi1, Random::seed));
            const float &c111 = HashToSigned(Hash3D(xi1, yi1, zi1, Random::seed));

            // interpolate:
            float u00 = SmoothStepUnclamped(c000, c100, tx);
            float u10 = SmoothStepUnclamped(c010, c110, tx);

            float u01 = SmoothStepUnclamped(c001, c101, tx);
            float u11 = SmoothStepUnclamped(c011, c111, tx);

            float v0 = SmoothStepUnclamped(u00, u10, ty);
            float v1 = SmoothStepUnclamped(u01, u11, ty);

            return SmoothStepUnclamped(v0, v1, tz);
        }

        float PerlinNoise1D(const float &p)
        {
            int pi = FloorToInt(p);

            std::uint8_t p0 = toGrid(pi);
            std::uint8_t p1 = toGrid(p0 + 1);

            float tp = p - pi;

            const float g0 = randomDotGradPerlin(p0, tp);
            const float g1 = randomDotGradPerlin(p1, tp - 1);

            return SmoothStepUnclamped5(g0, g1, tp);
        }
        float PerlinNoise2D(const Vector2 &p)
        {
            int xi = FloorToInt(p.X);
            int yi = FloorToInt(p.Y);

            int xi0 = toGrid(xi);
            int yi0 = toGrid(yi);

            int xi1 = toGrid(xi0 + 1);
            int yi1 = toGrid(yi0 + 1);

            float tx = p.X - xi;
            float ty = p.Y - yi;

            const float &c00 = randomDotGradPerlin(xi0, yi0, tx    , ty    );
            const float &c10 = randomDotGradPerlin(xi1, yi0, tx - 1, ty    );
            const float &c01 = randomDotGradPerlin(xi0, yi1, tx    , ty - 1);
            const float &c11 = randomDotGradPerlin(xi1, yi1, tx - 1, ty - 1);

            float u0 = SmoothStepUnclamped5(c00, c10, tx);
            float u1 = SmoothStepUnclamped5(c01, c11, tx);

            return SmoothStepUnclamped5(u0, u1, ty);
        }
        float PerlinNoise3D(const Vector3 &p)
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
            const float &c000 = randomDotGradPerlin(xi0, yi0, zi0, tx    , ty    , tz   );
            const float &c100 = randomDotGradPerlin(xi1, yi0, zi0, tx - 1, ty    , tz   );
            const float &c010 = randomDotGradPerlin(xi0, yi1, zi0, tx    , ty - 1, tz   );
            const float &c110 = randomDotGradPerlin(xi1, yi1, zi0, tx - 1, ty - 1, tz   );

            const float &c001 = randomDotGradPerlin(xi0, yi0, zi1, tx    , ty    , tz - 1);
            const float &c101 = randomDotGradPerlin(xi1, yi0, zi1, tx - 1, ty    , tz - 1);
            const float &c011 = randomDotGradPerlin(xi0, yi1, zi1, tx    , ty - 1, tz - 1);
            const float &c111 = randomDotGradPerlin(xi1, yi1, zi1, tx - 1, ty - 1, tz - 1);

            // interpolate:
            float u00 = SmoothStepUnclamped5(c000, c100, tx);
            float u10 = SmoothStepUnclamped5(c010, c110, tx);

            float u01 = SmoothStepUnclamped5(c001, c101, tx);
            float u11 = SmoothStepUnclamped5(c011, c111, tx);

            float v0 = SmoothStepUnclamped5(u00, u10, ty);
            float v1 = SmoothStepUnclamped5(u01, u11, ty);

            return SmoothStepUnclamped5(v0, v1, tz);
        }

        NoiseFunction1D GetBaseNoiseFunction1D(NoiseTypeEnum noiseType)
        {
            NoiseFunction1D result = nullptr;

            switch(noiseType)
            {
            case NoiseTypeEnum::White:
                result = WhiteNoise1D;
                break;
            case NoiseTypeEnum::Value:
                result = ValueNoise1D;
                break;
            case NoiseTypeEnum::Perlin:
                result = PerlinNoise1D;
                break;
            default:
                break;
            }
            return result;
        }
        NoiseFunction2D GetBaseNoiseFunction2D(NoiseTypeEnum noiseType)
        {
            NoiseFunction2D result = nullptr;

            switch(noiseType)
            {
            case NoiseTypeEnum::White:
                result = WhiteNoise2D;
                break;
            case NoiseTypeEnum::Value:
                result = ValueNoise2D;
                break;
            case NoiseTypeEnum::Perlin:
                result = PerlinNoise2D;
                break;
            default:
                break;
            }
            return result;
        }
        NoiseFunction3D GetBaseNoiseFunction3D(NoiseTypeEnum noiseType)
        {
            NoiseFunction3D result = nullptr;

            switch(noiseType)
            {
            case NoiseTypeEnum::White:
                result = WhiteNoise3D;
                break;
            case NoiseTypeEnum::Value:
                result = ValueNoise3D;
                break;
            case NoiseTypeEnum::Perlin:
                result = PerlinNoise3D;
                break;
            default:
                break;
            }
            return result;
        }

        void SetNumberOfOctaves(std::uint32_t numberOfOctaves)
        {
            Random::numberOfOctaves = numberOfOctaves;
        }
        void SetStartFrequency(float frequency)
        {
            Random::startFrequency = frequency;
        }
        void SetLacunarity(float lacunarity)
        {
            Random::lacunarity = lacunarity;
        }
        void SetPersistence(float persistence)
        {
            Random::persistence = persistence;
        }

        void SetNormalizeFBM(bool normalizeFBM)
        {
            Random::normalizeFBM = normalizeFBM;
        }
        void SetExponent(float exponent)
        {
            Random::exponent = exponent;
        }

        float FBM1D(const float &p, const FBMParameters &parameters, NoiseFunction1D noiseFun)
        {
            float result = 0.0f;

            float frequency = Random::startFrequency;
            float amplitude = 1.0f;

            float t = 0.0f;

            for(std::uint32_t i = 0; i < Random::numberOfOctaves; ++i)
            {
                result += amplitude*noiseFun(p*frequency);

                t += amplitude;
                frequency *= Random::lacunarity;
                amplitude *= Random::persistence;
            }

            if(Random::normalizeFBM)
            {
                result = result / t;
            }

            return std::pow(result, Random::exponent);
        }
        float FBM2D(const Vector2 &p, const FBMParameters &parameters, NoiseFunction2D noiseFun)
        {
            float result = 0.0f;

            float frequency = Random::startFrequency;
            float amplitude = 1.0f;

            float t = 0.0f;

            for(std::uint32_t i = 0; i < Random::numberOfOctaves; ++i)
            {
                result += amplitude*noiseFun(p*frequency);

                t += amplitude;
                frequency *= Random::lacunarity;
                amplitude *= Random::persistence;
            }

            if(Random::normalizeFBM)
            {
                result = result / t;
            }

            return std::pow(result, Random::exponent);
        }
        float FBM3D(const Vector3 &p, const FBMParameters &parameters, NoiseFunction3D noiseFun)
        {
            float result = 0.0f;

            float frequency = Random::startFrequency;
            float amplitude = 1.0f;

            float t = 0.0f;

            for(std::uint32_t i = 0; i < Random::numberOfOctaves; ++i)
            {
                result += amplitude*noiseFun(p*frequency);

                t += amplitude;
                frequency *= Random::lacunarity;
                amplitude *= Random::persistence;
            }

            if(Random::normalizeFBM)
            {
                result = result / t;
            }

            return std::powf(result, Random::exponent);
        }

        NoiseFunction1D Billow1D(NoiseFunction1D noiseFun)
        {
            return [noiseFun](const float &p)
            {
                return std::abs(noiseFun(p));
            };
        }
        NoiseFunction2D Billow2D(NoiseFunction2D noiseFun)
        {
            return [noiseFun](const Vector2 &p)
            {
                return std::abs(noiseFun(p));
            };
        }
        NoiseFunction3D Billow3D(NoiseFunction3D noiseFun)
        {
            return [noiseFun](const Vector3 &p)
            {
                return std::abs(noiseFun(p));
            };
        }

        NoiseFunction1D Ridge1D(NoiseFunction1D noiseFun)
        {
            return [noiseFun](const float &p)
            {
                float n = (0.9f - std::abs(noiseFun(p)));
                return n*n;
            };
        }
        NoiseFunction2D Ridge2D(NoiseFunction2D noiseFun)
        {
            return [noiseFun](const Vector2 &p)
            {
                float n = (0.9f - std::abs(noiseFun(p)));
                return n*n;
            };
        }
        NoiseFunction3D Ridge3D(NoiseFunction3D noiseFun)
        {
            return [noiseFun](const Vector3 &p)
            {
                float n = (0.9f - std::abs(noiseFun(p)));
                return n*n;
            };
        }


        NoiseTransform1D GetNoiseStyleTransform1D(NoiseStyleEnum noiseStyle)
        {
            NoiseTransform1D result = nullptr;

            switch(noiseStyle)
            {
            case NoiseStyleEnum::Plain:
                break;
            case NoiseStyleEnum::Billow:
                result = Billow1D;
                break;
            case NoiseStyleEnum::Ridge:
                result = Ridge1D;
                break;
            default:
                break;
            }
            return result;
        }
        NoiseTransform2D GetNoiseStyleTransform2D(NoiseStyleEnum noiseStyle)
        {
            NoiseTransform2D result = nullptr;

            switch(noiseStyle)
            {
            case NoiseStyleEnum::Plain:
                break;
            case NoiseStyleEnum::Billow:
                result = Billow2D;
                break;
            case NoiseStyleEnum::Ridge:
                result = Ridge2D;
                break;
            default:
                break;
            }
            return result;
        }
        NoiseTransform3D GetNoiseStyleTransform3D(NoiseStyleEnum noiseStyle)
        {
            NoiseTransform3D result = nullptr;

            switch(noiseStyle)
            {
            case NoiseStyleEnum::Plain:
                break;
            case NoiseStyleEnum::Billow:
                result = Billow3D;
                break;
            case NoiseStyleEnum::Ridge:
                result = Ridge3D;
                break;
            default:
                break;
            }
            return result;
        }
    }
}
