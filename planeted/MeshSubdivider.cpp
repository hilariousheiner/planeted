#include "MeshSubdivider.h"

#include <map>
#include <vector>

namespace Planeted
{
    struct MeshSubdivider::Impl
    {
        Mesh *mesh;

        std::vector<TriangleIndices> newTris;
        std::map<std::pair<int, int>, int> middlePointIndexCache;

        int GetMiddlePoint(int p1, int p2)
        {
            std::pair<int, int> entry;
            if(p1 <= p2)
            {
                entry = {p1, p2};
            }
            else
            {
                entry = {p2, p1};
            }

            if(this->middlePointIndexCache.find(entry) == this->middlePointIndexCache.end())
            {
                Vector3 *point1 = this->mesh->GetVertex(p1);
                Vector3 *point2 = this->mesh->GetVertex(p2);

                float middleX = (point1->X + point2->X) / 2.0;
                float middleY = (point1->Y + point2->Y) / 2.0;
                float middleZ = (point1->Z + point2->Z) / 2.0;

                int i = this->mesh->AddVertex(middleX, middleY, middleZ);

                this->middlePointIndexCache[entry] = i;
            }
            return this->middlePointIndexCache[entry];
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

        for(TriangleIndices tri : this->pImpl->mesh->Triangles())
        {
            int v0 = this->pImpl->GetMiddlePoint(tri.v0, tri.v1);
            int v1 = this->pImpl->GetMiddlePoint(tri.v1, tri.v2);
            int v2 = this->pImpl->GetMiddlePoint(tri.v2, tri.v0);

            this->pImpl->newTris.push_back({tri.v0, v0, v2});
            this->pImpl->newTris.push_back({tri.v1, v1, v0});
            this->pImpl->newTris.push_back({tri.v2, v2, v1});
            this->pImpl->newTris.push_back({v0, v1, v2});
        }
        this->pImpl->mesh->SetTriangles(this->pImpl->newTris);
    }
}
