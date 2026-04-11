#ifndef PLANETED_POVR_H
#define PLANETED_POVR_H

#include <string>

#include "Mesh.h"
#include "Vector3.h"

namespace Planeted
{
    namespace POV
    {
        std::string MeshToPOVMesh2(const Mesh &mesh);
        std::string POVSceneFile(const char *modelFilename);
    }
}
#endif
