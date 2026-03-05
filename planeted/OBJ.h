#ifndef PLANETED_OBJ_H
#define PLANETED_OBJ_H

#include <string>

#include "Mesh.h"
#include "Vector3.h"

namespace Planeted
{
    namespace OBJ
    {
        std::string Vector3ToOBJ(Vector3 *vector3);
        std::string TriangleIndicesToOBJ(TriangleIndices *indices);

        std::string MeshToOBJ(Mesh& mesh);
    }
}
#endif // PLANETED_OBJ_H
