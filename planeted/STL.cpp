#include <iomanip>
#include <sstream>
#include <string.h>

#include "STL.h"

namespace Planeted
{
    namespace STL
    {
        std::string vector3ToSTL(const Vector3 &vector3)
        {
            std::stringstream stream;

            stream << std::fixed << std::setprecision(4);
            stream << vector3.X << " " << vector3.Y << " " << vector3.Z;

            return stream.str();
        }

        std::string MeshToSTL(const Mesh &mesh)
        {
            std::stringstream stream;

            stream << "solid mesh\n";

            for(TriangleIndices tri : mesh.Triangles())
            {
                stream << "\t facet normal " << vector3ToSTL(mesh.GetNormal(tri.N)) << "\n";

                stream << "\t\t outer loop\n";
                stream << "\t\t\t vertex " << vector3ToSTL(mesh.GetVertex(tri.V0)) << "\n";
                stream << "\t\t\t vertex " << vector3ToSTL(mesh.GetVertex(tri.V1)) << "\n";
                stream << "\t\t\t vertex " << vector3ToSTL(mesh.GetVertex(tri.V2)) << "\n";
                stream << "\t\t endloop\n";

                stream << "\t endfacet\n";
            }
            stream << "endsolid";

            return stream.str();
        }
    }
}
