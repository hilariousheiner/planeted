#ifndef PLANETED_PDSL_LIB_H
#define PLANETED_PDSL_LIB_H

#include "PDSL.h"

namespace Planeted
{
    namespace PDSL_Lib
    {
        inline void Load(PDSL_Runtime &runtime)
        {
            runtime.InstallBuiltinFunction("icosahedron",
                [](PDSL_Runtime &runtime, const std::vector<Value> &args)
            {
                if(args.size() != 1)
                {
                    throw std::runtime_error("icosahedron expects exactly one argument.");
                }
                return Value(MakeIcosahedron(args[0].ToString()));
            });

            runtime.InstallBuiltinFunction("subdivide",
                [](PDSL_Runtime &runtime, const std::vector<Value> &args)
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
            });

            runtime.InstallBuiltinFunction("seedNoise",
                [](PDSL_Runtime &runtime, const std::vector<Value> &args)
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
            });

            runtime.InstallBuiltinFunction("displace",
                [](PDSL_Runtime &runtime, const std::vector<Value> &args)
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
                    float scalar = 1 + a * Random::FBM3D(*vertex, Random::ValueNoise3D);
                    *vertex *= scalar;
                }
                m->CalculateNormals(NormalTypeEnum::PerVertex);

                return Value(m);
            });
        }
    }
}
#endif
