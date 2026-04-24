#ifndef PLANETED_SCAD_H
#define PLANETED_SCAD_H

#include <string>

#include "Mesh.h"

namespace Planeted
{
    namespace SCAD
    {
        std::string MeshToSCAD(const Mesh &mesh);
    }
}
#endif
