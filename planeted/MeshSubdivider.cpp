#include "MeshSubdivider.h"

namespace Planeted
{
    struct MeshSubdivider::Impl
    {
        Mesh *mesh;
    };

    MeshSubdivider::MeshSubdivider(Mesh *mesh)
        : pImpl(new MeshSubdivider::Impl())
    {
        this->pImpl->mesh = mesh;
    }

    MeshSubdivider::~MeshSubdivider() = default;

    void MeshSubdivider::Subdivide()
    {

    }
}
