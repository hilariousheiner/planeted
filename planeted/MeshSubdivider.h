#ifndef PLANETED_MESHSUBDIVIDER_H
#define PLANETED_MESHSUBDIVIDER_H

#include <memory>

#include "Mesh.h"

namespace Planeted
{
    class MeshSubdivider
    {
    public:
        MeshSubdivider(Mesh *mesh);
        ~MeshSubdivider();
        void Subdivide();
    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };
}
#endif // PLANETED_MESHSUBDIVIDER_H
