#include "PDSL_Lib.h"

#include <iostream>

#include "Noise.h"
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

        static Value builtin_seedNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("seedNoise expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Int)
            {
                int seed = args[0].GetIntValue();
                Random::SeedNoise(seed);
            }
            else if(args[0].GetValueType() == ValueTypeEnum::String)
            {
                std::string seed = args[0].GetStringValue();
                Random::SeedNoise(seed);
            }
            else
            {
                throw std::runtime_error("seed must be an integer or a string.");
            }
            return Value::Null();
        }

        static Value builtin_setNoiseType(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setNoiseType expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Int)
            {
                noise.noiseType = toNoiseType(args[0].GetIntValue());
            }
            else
            {
                throw std::runtime_error("argument passed to setNoiseType must be an integer.");
            }
            return Value::Null();
        }
        static Value builtin_setNoiseStyle(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setNoiseStyle expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Int)
            {
                noise.noiseStyle = toNoiseStyle(args[0].GetIntValue());
            }
            else
            {
                throw std::runtime_error("argument passed to setNoiseStyle must be an integer.");
            }
            return Value::Null();
        }

        static Value builtin_setNumberOfOctaves(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setNumberOfOctaves expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Int)
            {
                Random::SetNumberOfOctaves(args[0].GetIntValue());
            }
            return Value::Null();
        }
        static Value builtin_setStartFrequency(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setStartFrequency expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Float)
            {
                Random::SetStartFrequency(args[0].GetFloatValue());
            }
            return Value::Null();
        }

        static Value builtin_setLacunarity(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setLacunarity expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Float)
            {
                Random::SetLacunarity(args[0].GetFloatValue());
            }
            else
            {
                throw std::runtime_error("argument passed to setLacunarity must be a float.");
            }
            return Value::Null();
        }

        static Value builtin_setPersistence(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setPersistence expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Float)
            {
                Random::SetPersistence(args[0].GetFloatValue());
            }
            else
            {
                throw std::runtime_error("argument passed to setPersistence must be a float.");
            }
            return Value::Null();
        }

        static Value builtin_setNormalizeFBM(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setNormalizeFBM expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Bool)
            {
                Random::SetNormalizeFBM(args[0].GetBoolValue());
            }
            else
            {
                throw std::runtime_error("argument passed to setNormalizeFBM must be a bool.");
            }
            return Value::Null();
        }

        static Value builtin_setExponent(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setExponent expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Float)
            {
                Random::SetExponent(args[0].GetFloatValue());
            }
            else
            {
                throw std::runtime_error("argument passed to setExponent must be a float.");
            }
            return Value::Null();
        }

        static Value builtin_setWhiteNoiseScale(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("setWhiteNoiseScale expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::Float)
            {
                Random::SetWhiteNoiseScale(args[0].GetFloatValue());
            }
            else
            {
                throw std::runtime_error("argument passed to setWhiteNoiseScale must be a float.");
            }
            return Value::Null();
        }

        static Value builtin_resetNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            Random::ResetNoise();
            return Value::Null();
        }

        static Value builtin_noiseTest(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("noiseTest expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::String)
            {
                std::string filename = NormalizePath(runtime.OutPath + args[0].GetStringValue());
                NoiseTest3D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise());
            }
            else
            {
                throw std::runtime_error("argument passed to noiseTest must be a string.");
            }
            return Value::Null();
        }
        static Value builtin_noiseTest2D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("noiseTest2D expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::String)
            {
                std::string filename = NormalizePath(runtime.OutPath + args[0].GetStringValue());
                NoiseTest2D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise2D());
            }
            else
            {
                throw std::runtime_error("argument passed to noiseTest2D must be a string.");
            }
            return Value::Null();
        }
        static Value builtin_noiseTest1D(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("noiseTest1D expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::String)
            {
                std::string filename = NormalizePath(runtime.OutPath + args[0].GetStringValue());
                NoiseTest1D(filename, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise1D());
            }
            else
            {
                throw std::runtime_error("argument passed to noiseTest1D must be a string.");
            }
            return Value::Null();
        }

        static Value builtin_subdivide(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 2)
            {
                throw std::runtime_error("subdivide expects two arguments.");
            }

            Mesh *m = args[0].ToMesh();
            int d = args[1].GetIntValue();

            m->Subdivide(d);

            return Value(m);
        }
        static Value builtin_tessellate(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 2)
            {
                throw std::runtime_error("tessellate expects two arguments.");
            }

            Mesh *m = args[0].ToMesh();
            int n = args[1].GetIntValue();

            m->Tessellate(n);

            return Value(m);
        }
        static Value builtin_projectToUnitSphere(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("projectToUnitSphere expects an argument.");
            }

            Mesh *m = args[0].ToMesh();
            m->ProjectToUnitSphere();

            return Value(m);
        }
        static Value builtin_calculateNormals(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("calculateNormals expects an argument.");
            }

            Mesh *m = args[0].ToMesh();
            m->CalculateNormals();

            return Value(m);
        }

        static float displaceFun(const Vector3 &v)
        {
            return Random::FBM3D(v, noise.fbmParams, noise.noiseParams, PDSL_Lib::getCurrentNoise());
        }
        static Value builtin_displace(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() < 2)
            {
                throw std::runtime_error("displace expects at least two arguments.");
            }

            Mesh *m = args[0].ToMesh();
            float a = args[1].GetFloatValue();

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
            runtime.InstallBuiltinFunction("seedNoise", builtin_seedNoise);

            runtime.InstallBuiltinFunction("setNoiseType", builtin_setNoiseType);
            runtime.InstallBuiltinFunction("setNoiseStyle", builtin_setNoiseStyle);
            runtime.InstallBuiltinFunction("resetNoise", builtin_resetNoise);

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
