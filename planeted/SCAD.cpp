#include <iomanip>
#include <sstream>
#include <string.h>

#include "SCAD.h"
#include "Utils.h"

namespace Planeted
{
    namespace SCAD
    {
        std::string vector3ToSCAD(const Vector3 &vector3)
        {
            std::stringstream stream;

            stream << std::fixed << std::setprecision(4);
            stream << "[" << vector3.X << ", " << vector3.Y << ", " << vector3.Z << "]";

            return stream.str();
        }

        std::string triangleIndicesToSCAD(const TriangleIndices &indices)
        {
            std::stringstream stream;

            stream << "[" << indices.V0 << ", " << indices.V1 << ", " << indices.V2 << "]";

            return stream.str();
        }

        std::string MeshToSCAD(const Mesh &mesh)
        {
            std::stringstream stream;

            stream << "module " << mesh.GetName() << "()\n";
            stream << "{\n";
            stream << "\t polyhedron(\n";

            stream << "\t\t points = [\n";
            stream << "\t\t\t" << listToString<Vector3>(mesh.Vertices(), vector3ToSCAD) << "\n";
            stream << "\t\t ],\n";

            stream << "\t\t faces = [\n";
            stream << "\t\t\t" << listToString<TriangleIndices>(mesh.Triangles(), triangleIndicesToSCAD) << "\n";
            stream << "\t\t ]\n";

            stream << "\t);\n";
            stream << "}\n";
            stream << mesh.GetName() << "();\n";

            return stream.str();
        }
    }
}
