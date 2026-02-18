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
            stream << "<" << vector3->GetX() << "," << vector3->GetY() << "," << vector3->GetZ() << ">";

            return stream.str();
        }

        std::string MeshToPOVMesh2(Mesh *mesh)
        {
            std::stringstream stream;

            stream << "mesh2\n";
            stream << "{\n";

            /* ... */

            stream << "}";

            return stream.str();
        }


        const char * sceneTemplate =
            "#include \"colors.inc\"\n"
            "#declare MODEL = union { #include \"%s\" }";

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
