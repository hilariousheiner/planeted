#ifndef PLANETED_MESHSUBDIVIDER_H
#define PLANETED_MESHSUBDIVIDER_H

#include "Mesh.h"

namespace Planeted
{
    class MeshSubdivider
    {
    private:
        Mesh *mesh;
    public:
        MeshSubdivider(Mesh *mesh);
        void Subdivide();
    };
}
#endif // PLANETED_MESHSUBDIVIDER_H
