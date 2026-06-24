#include "MeshSubdivider.h"

#include <map>
#include <vector>

namespace Planeted
{
    struct MeshSubdivider::Impl
    {
        Mesh *mesh;

        std::vector<TriangleIndices> newTris;
        std::map<std::pair<size_t, size_t>, size_t> middlePointIndexCache;

        size_t GetMiddlePoint(size_t p1, size_t p2)
        {
            std::pair<size_t, size_t> entry;
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
                const Vector3 &point1 = this->mesh->GetVertex(p1);
                const Vector3 &point2 = this->mesh->GetVertex(p2);

                float middleX = (point1.X + point2.X) / 2.0;
                float middleY = (point1.Y + point2.Y) / 2.0;
                float middleZ = (point1.Z + point2.Z) / 2.0;

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
            size_t v0 = this->pImpl->GetMiddlePoint(tri.V0, tri.V1);
            size_t v1 = this->pImpl->GetMiddlePoint(tri.V1, tri.V2);
            size_t v2 = this->pImpl->GetMiddlePoint(tri.V2, tri.V0);

            this->pImpl->newTris.push_back({tri.V0, v0, v2});
            this->pImpl->newTris.push_back({tri.V1, v1, v0});
            this->pImpl->newTris.push_back({tri.V2, v2, v1});
            this->pImpl->newTris.push_back({v0, v1, v2});
        }
        this->pImpl->mesh->SetTriangles(this->pImpl->newTris);
    }
}
