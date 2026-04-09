#ifndef PLANETED_STL_H
#define PLANETED_STL_H

#include <string>

#include "Mesh.h"
#include "Vector3.h"

namespace Planeted
{
    namespace STL
    {
        std::string MeshToSTL(Mesh &mesh);
    }
}
#endif
