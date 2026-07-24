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
        static Noise noise;

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

        static Random::NoiseFunction3D getCurrentNoise()
        {
            return Random::GetNoiseFunction3D(noise.noiseType, noise.noiseStyle);
        }
        static Random::NoiseFunction2D getCurrentNoise2D()
        {
            return Random::GetNoiseFunction2D(noise.noiseType, noise.noiseStyle);
        }
        static Random::NoiseFunction1D getCurrentNoise1D()
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
            ExpectArgsCount(args, 1, "seedNoise");

            if(args[0].GetValueType() == ValueTypeEnum::Int)
            {
                int seed = args[0].GetIntValue();
                noise.noiseParams.SeedNoise(seed);
            }
            else if(args[0].GetValueType() == ValueTypeEnum::String)
            {
                std::string seed = args[0].GetStringValue();
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
            ExpectArgsCount(args, 1, "setNoiseType");

            noise.noiseType = toNoiseType(GetIntArg(args, 0, "setNoiseType"));

            return Value::Null();
        }
        static Value builtin_setNoiseStyle(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "setNoiseStyle");

            noise.noiseStyle = toNoiseStyle(GetIntArg(args, 0, "setNoiseStyle"));

            return Value::Null();
        }

        static Value builtin_setNumberOfOctaves(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "setNumberOfOctaves");

            noise.SetNumberOfOctaves(GetIntArg(args, 0, "setNumberOfOctaves"));

            return Value::Null();
        }
        static Value builtin_setStartFrequency(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "setStartFrequency");

            noise.SetStartFrequency(GetFloatArg(args, 0, "setStartFrequency"));

            return Value::Null();
        }

        static Value builtin_setLacunarity(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "setLacunarity");

            noise.SetLacunarity(GetFloatArg(args, 0, "setLacunarity"));

            return Value::Null();
        }

        static Value builtin_setPersistence(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "setPersistence");

            noise.SetPersistence(GetFloatArg(args, 0, "setPersistence"));

            return Value::Null();
        }

        static Value builtin_setNormalizeFBM(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "setNormalizeFBM");

            noise.SetNormalizeFBM(GetBoolArg(args, 0, "setNormalizeFBM"));

            return Value::Null();
        }

        static Value builtin_setExponent(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "setExponent");

            noise.SetExponent(GetFloatArg(args, 0, "setExponent"));

            return Value::Null();
        }

        static Value builtin_setWhiteNoiseScale(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "setWhiteNoiseScale");

            noise.SetWhiteNoiseScale(GetFloatArg(args, 0, "setWhiteNoiseScale"));

            return Value::Null();
        }

        static Value builtin_noiseTest(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "noiseTest");

            std::string filename = GetStringArg(args, 0, "noiseTest");
            filename = NormalizePath(runtime.OutPath + filename);
            NoiseTest3D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise());

            return Value::Null();
        }
        static Value builtin_noiseTest2D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "noiseTest2D");

            std::string filename = GetStringArg(args, 0, "noiseTest2D");
            filename = NormalizePath(runtime.OutPath + filename);
            NoiseTest2D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise2D());

            return Value::Null();
        }
        static Value builtin_noiseTest1D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "noiseTest1D");

            std::string filename = GetStringArg(args, 0, "noiseTest1D");
            filename = NormalizePath(runtime.OutPath + filename);
            NoiseTest1D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise1D());

            return Value::Null();
        }

        static Value builtin_subdivide(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "subdivide");

            Mesh *m = ToMesh(args[0]);

            int d = GetIntArg(args, 1, "subdivide");

            m->Subdivide(d);

            return Value(m);
        }
        static Value builtin_tessellate(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 2, "tessellate");

            Mesh *m = ToMesh(args[0]);
            int n = args[1].GetIntValue();

            m->Tessellate(n);

            return Value(m);
        }
        static Value builtin_projectToUnitSphere(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "projectToUnitSphere");

            Mesh *m = ToMesh(args[0]);
            m->ProjectToUnitSphere();

            return Value(m);
        }
        static Value builtin_calculateNormals(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCount(args, 1, "calculateNormals");

            Mesh *m = ToMesh(args[0]);
            m->CalculateNormals();

            return Value(m);
        }

        static float displaceFun(const Vector3 &v)
        {
            return Random::FBM3D(v, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise());
        }
        static Value builtin_displace(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            ExpectArgsCountAtLeast(args, 2, "displace");
            ExpectArgsCountAtMost(args, 3, "displace");

            Mesh *m = ToMesh(args[0]);
            float a = GetFloatArg(args, 1, "displace");//args[1].GetFloatValue();

            DisplacementTypeEnum displacementType = DisplacementTypeEnum::Normal;
            if(args.size() == 3)
            {
                displacementType = toDisplacementType(args[2].GetIntValue());
            }

            m->Displace(displaceFun, a, displacementType);
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
