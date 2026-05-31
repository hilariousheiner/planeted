#include "PDSL_Lib.h"

#include <iostream>

#include "MeshSubdivider.h"
#include "Random.h"

namespace Planeted
{
    namespace PDSL_Lib
    {
        static Random::NoiseTypeEnum noiseType = Random::NoiseTypeEnum::Value;

        Random::NoiseTypeEnum toNoiseType(int type)
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

        Random::NoiseFunction3D getCurrentNoise()
        {
            Random::NoiseFunction3D result = nullptr;

            switch(PDSL_Lib::noiseType)
            {
            case Random::NoiseTypeEnum::White:
                std::cout << "white noise" << std::endl;
                result = Random::ValueNoise3D;
                break;
            case Random::NoiseTypeEnum::Value:
                result = Random::ValueNoise3D;
                break;
            case Random::NoiseTypeEnum::Perlin:
                result = Random::PerlinNoise3D;
                break;
            default:
                break;
            }
            return result;
        }

        Value builtin_icosahedron(PDSL_Runtime &runtime, const std::vector<Value> &args)
        {
            if(args.size() != 1)
            {
                throw std::runtime_error("icosahedron expects exactly one argument.");
            }
            return Value(MakeIcosahedron(args[0].ToString()));
        }

        Value builtin_subdivide(PDSL_Runtime &runtime, const std::vector<Value> &args)
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

        Value builtin_seedNoise(PDSL_Runtime &runtime, const std::vector<Value> &args)
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

        Value builtin_setNoiseType(PDSL_Runtime &runtime, const std::vector<Value> &args)
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

        Value builtin_displace(PDSL_Runtime &runtime, const std::vector<Value> &args)
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
                float scalar = 1 + a * Random::FBM3D(*vertex, PDSL_Lib::getCurrentNoise());
                *vertex *= scalar;
            }
            m->CalculateNormals(NormalTypeEnum::PerVertex);

            return Value(m);
        }

        void Load(PDSL_Runtime &runtime)
        {
            runtime.InstallBuiltinFunction("icosahedron", builtin_icosahedron);
            runtime.InstallBuiltinFunction("subdivide", builtin_subdivide);
            runtime.InstallBuiltinFunction("seedNoise", builtin_seedNoise);
            runtime.InstallBuiltinFunction("setNoiseType", builtin_setNoiseType);
            runtime.InstallBuiltinFunction("displace", builtin_displace);
        }
    }
}
