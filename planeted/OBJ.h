#ifndef PLANETED_OBJ_H
#define PLANETED_OBJ_H

#include <string>

#include "Mesh.h"
#include "Vector3.h"

namespace Planeted
{
    namespace OBJ
    {
        std::string MeshToOBJ(const Mesh &mesh);
    }
}
#endif // PLANETED_OBJ_H
