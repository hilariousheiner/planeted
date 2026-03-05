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

        std::string TriangleIndicesToOBJ(TriangleIndices *indices)
        {
            std::stringstream stream;

            stream << "f " << indices->a + 1 << " " << indices->b + 1 << " " << indices->c + 1;

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

            for(TriangleIndices i : mesh.Triangles())
            {
                stream << TriangleIndicesToOBJ(&i) << "\n";
            }
            return stream.str();
        }
    }
}
