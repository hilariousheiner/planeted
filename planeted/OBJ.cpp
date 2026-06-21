#include <iomanip>
#include <sstream>
#include <string.h>

#include "OBJ.h"

namespace Planeted
{
    namespace OBJ
    {
        std::string vertex3ToOBJ(const Vector3 &vector3)
        {
            std::stringstream stream;

            stream << std::fixed << std::setprecision(4);
            stream << "v " << vector3.X << " " << vector3.Y << " " << vector3.Z;

            return stream.str();
        }

        /*
        std::string normalToOBJ(const Vector3 &normal)
        {
            std::stringstream stream;

            stream << std::fixed << std::setprecision(4);
            stream << "vn " << normal.X << " " << normal.Y << " " << normal.Z;

            return stream.str();
        }
        */

        std::string triangleIndicesToOBJ(const TriangleIndices &indices, NormalTypeEnum normalType)
        {
            std::stringstream stream;

            stream << "f ";
            stream << indices.V0 + 1 << " ";
            stream << indices.V1 + 1 << " ";
            stream << indices.V2 + 1;

            /*
            switch(normalType)
            {
                case NormalTypeEnum::PerFace:
                    stream << indices.V0 + 1 << "//" << indices.N + 1 << " ";
                    stream << indices.V1 + 1 << "//" << indices.N + 1<< " ";
                    stream << indices.V2 + 1 << "//" << indices.N + 1;
                    break;
                case NormalTypeEnum::PerVertex:
                    stream << indices.V0 + 1 << "//" << indices.V0 + 1 << " ";
                    stream << indices.V1 + 1 << "//" << indices.V1 + 1<< " ";
                    stream << indices.V2 + 1 << "//" << indices.V2 + 1;
                    break;
                case NormalTypeEnum::None:
                default:
                    stream << indices.V0 + 1 << " ";
                    stream << indices.V1 + 1 << " ";
                    stream << indices.V2 + 1;
                    break;
            }
            */
            return stream.str();
        }

        std::string MeshToOBJ(const Mesh &mesh)
        {
            std::stringstream stream;

            for(Vector3 v : mesh.Vertices())
            {
                stream << vertex3ToOBJ(v) << "\n";
            }
            stream << "\n";

            /*
            for(Vector3 n : mesh.Normals())
            {
                stream << normalToOBJ(n) << "\n";
            }
            stream << "\n";
            */

            for(TriangleIndices i : mesh.Triangles())
            {
                stream << triangleIndicesToOBJ(i, mesh.GetNormalType()) << "\n";
            }
            return stream.str();
        }
    }
}
