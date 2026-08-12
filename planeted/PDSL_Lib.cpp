#include "PDSL_Lib.h"

#include <iostream>

#include "Noise.h"
#include "PDSL_Utils.h"
#include "Random.h"
#include "Tests.h"

namespace Planeted
{
    namespace PDSL_Lib
    {
        static DisplacementTypeEnum toDisplacementType(int type)
        {
            DisplacementTypeEnum result = DisplacementTypeEnum::Vertex;

            switch(type)
            {
            case 0:
                result = DisplacementTypeEnum::Vertex;
                break;
            case 1:
                result = DisplacementTypeEnum::Normal;
                break;
            default:
                break;
            }
            return result;
        }

        static Random::NoiseTypeEnum toNoiseType(int type)
        {
            Random::NoiseTypeEnum result = Random::NoiseTypeEnum::Value;

            switch(type)
            {
            case 0:
                result = Random::NoiseTypeEnum::White;
                break;
            case 1:
                result = Random::NoiseTypeEnum::Value;
                break;
            case 2:
                result = Random::NoiseTypeEnum::Perlin;
                break;
            case 3:
                result = Random::NoiseTypeEnum::Gradient;
                break;
            default:
                break;
            }
            return result;
        }
        static Random::NoiseStyleEnum toNoiseStyle(int style)
        {
            Random::NoiseStyleEnum result = Random::NoiseStyleEnum::Plain;

            switch(style)
            {
            case 0:
                result = Random::NoiseStyleEnum::Plain;
                break;
            case 1:
                result = Random::NoiseStyleEnum::Billow;
                break;
            case 2:
                result = Random::NoiseStyleEnum::Ridge;
                break;
            default:
                break;
            }
            return result;
        }

        static Random::NoiseFunction3D getCurrentNoise(const Noise &noise)
        {
            return Random::GetNoiseFunction3D(noise.noiseType, noise.noiseStyle);
        }
        static Random::NoiseFunction2D getCurrentNoise2D(const Noise &noise)
        {
            return Random::GetNoiseFunction2D(noise.noiseType, noise.noiseStyle);
        }
        static Random::NoiseFunction1D getCurrentNoise1D(const Noise &noise)
        {
            return Random::GetNoiseFunction1D(noise.noiseType, noise.noiseStyle);
        }

        static Value builtin_noise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 0, "noise");

            Noise *noise = new Noise();
            return Value(noise);
        }

        static Value builtin_seedNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "seedNoise");

            Noise &noise = GetNoiseArg(args, 0, "seedNoise");

            if(args[1].GetValueType() == ValueTypeEnum::Int)
            {
                int seed = args[1].GetIntValue();
                noise.noiseParams.SeedNoise(seed);
            }
            else if(args[1].GetValueType() == ValueTypeEnum::String)
            {
                std::string seed = args[1].GetStringValue();
                noise.noiseParams.SeedNoise(seed);
            }
            else
            {
                throw std::runtime_error("seed must be an integer or a string.");
            }
            return Value::Null();
        }

        static Value builtin_setNoiseType(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNoiseType");

            Noise &noise = GetNoiseArg(args, 0, "setNoiseType");
            noise.noiseType = toNoiseType(GetIntArg(args, 1, "setNoiseType"));

            return Value::Null();
        }
        static Value builtin_setNoiseStyle(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNoiseStyle");

            Noise &noise = GetNoiseArg(args, 0, "setNoiseStyle");
            noise.noiseStyle = toNoiseStyle(GetIntArg(args, 1, "setNoiseStyle"));

            return Value::Null();
        }

        static Value builtin_setNumberOfOctaves(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNumberOfOctaves");

            Noise &noise = GetNoiseArg(args, 0, "setNumberOfOctaves");
            noise.SetNumberOfOctaves(GetIntArg(args, 1, "setNumberOfOctaves"));

            return Value::Null();
        }
        static Value builtin_setStartFrequency(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setStartFrequency");

            Noise &noise = GetNoiseArg(args, 0, "setStartFrequency");
            noise.SetStartFrequency(GetFloatArg(args, 1, "setStartFrequency"));

            return Value::Null();
        }

        static Value builtin_setLacunarity(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setLacunarity");

            Noise &noise = GetNoiseArg(args, 0, "setLacunarity");
            noise.SetLacunarity(GetFloatArg(args, 1, "setLacunarity"));

            return Value::Null();
        }

        static Value builtin_setPersistence(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setPersistence");

            Noise &noise = GetNoiseArg(args, 0, "setPersistence");
            noise.SetPersistence(GetFloatArg(args, 1, "setPersistence"));

            return Value::Null();
        }

        static Value builtin_setNormalizeFBM(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setNormalizeFBM");

            Noise &noise = GetNoiseArg(args, 0, "setNormalizeFBM");
            noise.SetNormalizeFBM(GetBoolArg(args, 1, "setNormalizeFBM"));

            return Value::Null();
        }

        static Value builtin_setExponent(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setExponent");

            Noise &noise = GetNoiseArg(args, 0, "setExponent");
            noise.SetExponent(GetFloatArg(args, 1, "setExponent"));

            return Value::Null();
        }

        static Value builtin_setWhiteNoiseScale(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "setWhiteNoiseScale");

            Noise &noise = GetNoiseArg(args, 0, "setWhiteNoiseScale");
            noise.SetWhiteNoiseScale(GetFloatArg(args, 1, "setWhiteNoiseScale"));

            return Value::Null();
        }

        static Value builtin_noiseTest(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest");

            Noise &noise = GetNoiseArg(args, 0, "noiseTest");
            std::string filename = GetStringArg(args, 1, "noiseTest");

            filename = NormalizePath(runtime.OutPath + filename);
            NoiseTest3D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise(noise));

            return Value::Null();
        }
        static Value builtin_noiseTest2D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest2D");

            Noise &noise = GetNoiseArg(args, 0, "noiseTest2D");
            std::string filename = GetStringArg(args, 1, "noiseTest2D");

            filename = NormalizePath(runtime.OutPath + filename);
            NoiseTest2D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise2D(noise));

            return Value::Null();
        }
        static Value builtin_noiseTest1D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "noiseTest1D");

            Noise &noise = GetNoiseArg(args, 0, "noiseTest1D");
            std::string filename = GetStringArg(args, 1, "noiseTest1D");

            filename = NormalizePath(runtime.OutPath + filename);
            NoiseTest1D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise1D(noise));

            return Value::Null();
        }

        static Value builtin_subdivide(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "subdivide");

            Mesh m = GetMeshArg(args, 0, "subdivide");
            int d = GetIntArg(args, 1, "subdivide");

            m.Subdivide(d);

            return Value(m);
        }
        static Value builtin_tessellate(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "tessellate");

            Mesh m = GetMeshArg(args, 0, "tessellate");
            int n = args[1].GetIntValue();

            m.Tessellate(n);

            return Value(m);
        }
        static Value builtin_projectToUnitSphere(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "projectToUnitSphere");

            Mesh m = GetMeshArg(args, 0, "projectToUnitSphere");
            m.ProjectToUnitSphere();

            return Value(m);
        }
        static Value builtin_calculateNormals(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "calculateNormals");

            Mesh m = GetMeshArg(args, 0, "calculateNormals");
            m.CalculateNormals();

            return Value(m);
        }

        static DisplacementFunction noiseDisplaceFun(const Noise &noise)
        {
            return [noise](const Vector3 &v)
            {
                return Random::FBM3D(v, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise(noise));
            };
        }
        static Value builtin_displace(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtLeast(args, 3, "displace");
            ExpectArgsCountAtMost(args, 4, "displace");

            Mesh m = GetMeshArg(args, 0, "displace");
            Noise &noise = GetNoiseArg(args, 1, "displace");
            float a = GetFloatArg(args, 2, "displace");

            DisplacementTypeEnum displacementType = DisplacementTypeEnum::Normal;
            if(args.size() == 4)
            {
                displacementType = toDisplacementType(args[3].GetIntValue());
            }

            m.Displace(noiseDisplaceFun(noise), a, displacementType);
            return Value(m);
        }

        void Load(PDSL_Runtime &runtime)
        {
            runtime.InstallBuiltinFunction("noise", builtin_noise);
            runtime.InstallBuiltinFunction("seedNoise", builtin_seedNoise);

            runtime.InstallBuiltinFunction("setNoiseType", builtin_setNoiseType);
            runtime.InstallBuiltinFunction("setNoiseStyle", builtin_setNoiseStyle);

            runtime.InstallBuiltinFunction("setWhiteNoiseScale", builtin_setWhiteNoiseScale);

            runtime.InstallBuiltinFunction("setNumberOfOctaves", builtin_setNumberOfOctaves);
            runtime.InstallBuiltinFunction("setStartFrequency", builtin_setStartFrequency);
            runtime.InstallBuiltinFunction("setLacunarity", builtin_setLacunarity);
            runtime.InstallBuiltinFunction("setPersistence", builtin_setPersistence);
            runtime.InstallBuiltinFunction("setNormalizeFBM", builtin_setNormalizeFBM);
            runtime.InstallBuiltinFunction("setExponent", builtin_setExponent);

            runtime.InstallBuiltinFunction("subdivide", builtin_subdivide);
            runtime.InstallBuiltinFunction("tessellate", builtin_tessellate);
            runtime.InstallBuiltinFunction("projectToUnitSphere", builtin_projectToUnitSphere);
            runtime.InstallBuiltinFunction("calculateNormals", builtin_calculateNormals);
            runtime.InstallBuiltinFunction("displace", builtin_displace);

            runtime.InstallBuiltinFunction("noiseTest", builtin_noiseTest);
            runtime.InstallBuiltinFunction("noiseTest2D", builtin_noiseTest2D);
            runtime.InstallBuiltinFunction("noiseTest1D", builtin_noiseTest1D);
        }
    }
}
