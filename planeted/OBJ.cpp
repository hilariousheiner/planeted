#include <iomanip>
#include <sstream>
#include <string.h>

#include "OBJ.h"

namespace Planeted
{
    namespace OBJ
    {
        std::string Vector3ToOBJ(Vector3 *vector3)
        {
            std::stringstream stream;

            stream << std::fixed << std::setprecision(4);
            stream << "v " << vector3->X() << " " << vector3->Y() << " " << vector3->Z();

            return stream.str();
        }

        std::string NormalToOBJ(Vector3 *normal)
        {
            std::stringstream stream;

            stream << std::fixed << std::setprecision(4);
            stream << "vn " << normal->X() << " " << normal->Y() << " " << normal->Z();

            return stream.str();
        }

        std::string TriangleIndicesToOBJ(TriangleIndices *indices)
        {
            std::stringstream stream;

            stream << "f ";
            stream << indices->v0 + 1 << "//" << indices->n + 1 << " ";
            stream << indices->v1 + 1 << "//" << indices->n + 1<< " ";
            stream << indices->v2 + 1 << "//" << indices->n + 1;

            return stream.str();
        }

        std::string MeshToOBJ(Mesh& mesh)
        {
            std::stringstream stream;

            for(Vector3 v : mesh.Vertices())
            {
                stream << Vector3ToOBJ(&v) << "\n";
            }
            stream << "\n";

            for(Vector3 n : mesh.Normals())
            {
                stream << NormalToOBJ(&n) << "\n";
            }
            stream << "\n";

            for(TriangleIndices i : mesh.Triangles())
            {
                stream << TriangleIndicesToOBJ(&i) << "\n";
            }
            return stream.str();
        }
    }
}
