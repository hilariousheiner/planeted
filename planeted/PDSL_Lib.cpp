#include "PDSL_Lib.h"

#include <iostream>

#include "MeshSubdivider.h"
#include "Random.h"
#include "Tests.h"

namespace Planeted
{
    namespace PDSL_Lib
    {
        static Random::NoiseTypeEnum noiseType = Random::NoiseTypeEnum::Value;
        static Random::NoiseStyleEnum noiseStyle = Random::NoiseStyleEnum::Plain;

        static Random::FBMParameters fbmParams;
        static Random::NoiseParameters noiseParams;

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
            return Random::GetNoiseFunction3D(PDSL_Lib::noiseType, PDSL_Lib::noiseStyle);
        }
        static Random::NoiseFunction2D getCurrentNoise2D()
        {
            return Random::GetNoiseFunction2D(PDSL_Lib::noiseType, PDSL_Lib::noiseStyle);
        }
        static Random::NoiseFunction1D getCurrentNoise1D()
        {
            return Random::GetNoiseFunction1D(PDSL_Lib::noiseType, PDSL_Lib::noiseStyle);
        }

        static Value builtin_icosahedron(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("icosahedron expects exactly one argument.");
            }
            return Value(MakeIcosahedron(args[0].ToString()));
        }

        static Value builtin_subdivide(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 2)
            {
                throw std::runtime_error("subdivide expects two arguments.");
            }

            Mesh *m = args[0].GetMeshValue();
            int d = args[1].GetIntValue();

            MeshSubdivider subdivider(m);

            int i = 0;
            while(i < d)
            {
                subdivider.Subdivide();
                ++i;
            }

            m->ProjectToUnitSphere();

            return Value(m);
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
                PDSL_Lib::noiseType = toNoiseType(args[0].GetIntValue());
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
                PDSL_Lib::noiseStyle = toNoiseStyle(args[0].GetIntValue());
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

        static Value builtin_displace(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 2)
            {
                throw std::runtime_error("displace expects two arguments.");
            }

            Mesh *m = args[0].GetMeshValue();
            float a = args[1].GetFloatValue();

            for(int id = 0; id < m->VertexCount(); ++id)
            {
                Vector3 *vertex = m->GetVertex(id);
                float scalar = 1 + a * Random::FBM3D(*vertex, fbmParams, noiseParams, PDSL_Lib::getCurrentNoise());
                *vertex *= scalar;
            }
            m->CalculateNormals(NormalTypeEnum::PerVertex);

            return Value(m);
        }

        static Value builtin_noiseTest(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("noiseTest expects one argument.");
            }

            if(args[0].GetValueType() == ValueTypeEnum::String)
            {
                NoiseTest3D(args[0].GetStringValue(), fbmParams, noiseParams, PDSL_Lib::getCurrentNoise());
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
                NoiseTest2D(args[0].GetStringValue(), fbmParams, noiseParams, PDSL_Lib::getCurrentNoise2D());
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
                NoiseTest1D(args[0].GetStringValue(), fbmParams, noiseParams, PDSL_Lib::getCurrentNoise1D());
            }
            else
            {
                throw std::runtime_error("argument passed to noiseTest1D must be a string.");
            }
            return Value::Null();
        }

        void Load(PDSL_Runtime &runtime)
        {
            runtime.InstallBuiltinFunction("icosahedron", builtin_icosahedron);

            runtime.InstallBuiltinFunction("subdivide", builtin_subdivide);

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

            runtime.InstallBuiltinFunction("displace", builtin_displace);

            runtime.InstallBuiltinFunction("noiseTest", builtin_noiseTest);
            runtime.InstallBuiltinFunction("noiseTest2D", builtin_noiseTest2D);
            runtime.InstallBuiltinFunction("noiseTest1D", builtin_noiseTest1D);
        }
    }
}
