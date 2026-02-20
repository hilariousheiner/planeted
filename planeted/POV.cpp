#include <iomanip>
#include <sstream>
#include <string.h>

#include "POV.h"

namespace Planeted
{
    namespace POVR
    {
        std::string Vector3ToPOV(Vector3 *vector3)
        {
            std::stringstream stream;

            stream << std::fixed << std::setprecision(4);
            stream << "<" << vector3->X() << "," << vector3->Y() << "," << vector3->Z() << ">";

            return stream.str();
        }

        std::string TriangleIndicesToPOV(TriangleIndices *indices)
        {
            std::stringstream stream;

            stream << "<" << indices->a << "," << indices->b << "," << indices->c << ">";

            return stream.str();
        }

        std::string MeshToPOVMesh2(Mesh *mesh)
        {
            std::stringstream stream;

            stream << "mesh2\n";
            stream << "{\n";
            stream << "\tvertex_vectors\n";
            stream << "\t{\n";
            stream << "\t\t" << mesh->VertexCount();

            for(Vector3 v : mesh->Vertices())
            {
                stream << ",\n\t\t" << Vector3ToPOV(&v);
            }
            stream << "\n\t}\n";

            stream << "\tface_indices\n";
            stream << "\t{\n";
            stream << "\t\t" << mesh->TriangleCount();

            for(TriangleIndices i : mesh->Triangles())
            {
                stream << ",\n\t\t" << TriangleIndicesToPOV(&i);
            }
            stream << "\n\t}\n";

            stream << "}";

            return stream.str();
        }

        const char * sceneTemplate =
            "#include \"colors.inc\"\n"
            "\n"
            "camera\n"
            "{\n"
            "   location <0,10,-20>\n"
            "   look_at <0,0,0>\n"
            "   angle 0\n"
            "}\n"
            "\n"
            "light_source\n"
            "{\n"
            "   <-8, 22, 0>\n"
            "   color <1,1,1>\n"
            "}\n"
            "\n"
            "plane\n"
            "{\n"
            "   y, -10\n"
            "   pigment { checker Black, White }\n"
            "}\n"
            "\n"
            "union\n"
            "{\n"
            "   #include \"%s\"\n"
            "   pigment { Red }\n"
            "}";

        std::string POVSceneFile(const char *modelFilename)
        {
            char *buffer = new char[strlen(sceneTemplate) + strlen(modelFilename)];

            sprintf(buffer, sceneTemplate, modelFilename);
            std::string result = { buffer };

            delete[] buffer;

            return result;
        }
    }
}
