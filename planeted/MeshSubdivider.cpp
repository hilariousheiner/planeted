#include "MeshSubdivider.h"

#include <map>
#include <vector>

namespace Planeted
{
    struct MeshSubdivider::Impl
    {
        Mesh *mesh;

        std::vector<Vector3> newTris;
        std::map<std::pair<int, int>, int> middlePointIndexCache;

        int getMiddlePoint(int p1, int p2)
        {
            if(this->middlePointIndexCache.find({p1, p2}) == this->middlePointIndexCache.end())
            {
                Vector3 *point1 = this->mesh->GetVertex(p1);
                Vector3 *point2 = this->mesh->GetVertex(p2);

                float middleX = (point1->X() + point2->X()) / 2.0;
                float middleY = (point1->Y() + point2->Y()) / 2.0;
                float middleZ = (point1->Z() + point2->Z()) / 2.0;

                int i = this->mesh->AddVertex(middleX, middleY, middleZ);

                this->middlePointIndexCache[{p1, p2}] = i;
            }
            return this->middlePointIndexCache[{p1, p2}];
        }
    };

    MeshSubdivider::MeshSubdivider(Mesh *mesh)
        : pImpl(new MeshSubdivider::Impl())
    {
        this->pImpl->mesh = mesh;
    }

    MeshSubdivider::~MeshSubdivider() = default;

    void MeshSubdivider::Subdivide()
    {
        this->pImpl->newTris.clear();
        this->pImpl->middlePointIndexCache.clear();

        for(TriangleIndices i : this->pImpl->mesh->Triangles())
        {

        }
    }
}
