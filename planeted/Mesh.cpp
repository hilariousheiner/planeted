#include "Mesh.h"
#include <iostream>
#include <stdexcept>

namespace Planeted
{
    Mesh::Mesh()
      : name("mesh")
    {}

    Mesh::Mesh(std::string name)
        : name(std::move(name))
    {}

    const std::string &Mesh::GetName() const
    {
        return this->name;
    }
    void Mesh::SetName(std::string name)
    {
        this->name = std::move(name);
    }

    size_t Mesh::AddVertex(float x, float y, float z)
    {
        int result = this->vertices.size();

        this->vertices.push_back(Vector3 {x, y, z});

        return result;
    }

    void Mesh::TranslateVertex(size_t id, const Vector3 &t)
    {
        this->vertices[id] += t;
    }

    const Vector3 &Mesh::GetVertex(size_t id) const
    {
        if(id >= this->vertices.size())
        {
            throw std::out_of_range("Index out of bounds");
        }
        return this->vertices[id];
    }

    const Vector3 &Mesh::GetNormal(size_t id) const
    {
        if(id >= this->normals.size())
        {
            throw std::out_of_range("Index out of bounds");
        }
        return this->normals[id];
    }

    void Mesh::AddTriangle(size_t a, size_t b, size_t c)
    {
        this->triangles.push_back(TriangleIndices {a, b, c});
    }

    void Mesh::SetTriangles(std::vector<TriangleIndices> tris)
    {
        this->triangles.clear();
        for(TriangleIndices tri : tris)
        {
            this->AddTriangle(tri.V0, tri.V1, tri.V2);
        }
    }

    size_t Mesh::VertexCount() const
    {
        return this->vertices.size();
    }
    int Mesh::TriangleCount() const
    {
        return this->triangles.size();
    }

    const std::vector<Vector3> &Mesh::Vertices() const
    {
        return this->vertices;
    }

    const std::vector<Vector3> &Mesh::Normals() const
    {
        return this->normals;
    }

    const std::vector<TriangleIndices> &Mesh::Triangles() const
    {
        return this->triangles;
    }

    void Mesh::ProjectToUnitSphere()
    {
        for(Vector3 &v : this->vertices)
        {
            v.Normalize();
        }
    }

    void Mesh::CalculateNormals()
    {
        this->normals.resize(this->vertices.size());

        for(TriangleIndices &i : this->triangles)
        {
            Vector3 normal = this->CalculateNormal(i);

            this->normals[i.V0] += normal;
            this->normals[i.V1] += normal;
            this->normals[i.V2] += normal;
        }

        for(Vector3 &normal : this->normals)
        {
            normal.Normalize();
        }
    }

    Vector3 Mesh::CalculateNormal(TriangleIndices &tri) const
    {
        const Vector3 &v0 = this->vertices[tri.V0];
        const Vector3 &v1 = this->vertices[tri.V1];
        const Vector3 &v2 = this->vertices[tri.V2];

        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;

        Vector3 normal = edge1.Cross(edge2);

        return normal;
    }

    size_t Mesh::AddMiddlePoint(size_t v1, size_t v2)
    {
        std::pair<size_t, size_t> key;
        if(v1 <= v2)
        {
            key = {v1, v2};
        }
        else
        {
            key= {v2, v1};
        }

        if(this->middlePointIndexCache.find(key) == this->middlePointIndexCache.end())
        {
            const Vector3 &vertex1 = this->GetVertex(v1);
            const Vector3 &vertex2 = this->GetVertex(v2);

            float middleX = (vertex1.X + vertex2.X) / 2.0;
            float middleY = (vertex1.Y + vertex2.Y) / 2.0;
            float middleZ = (vertex1.Z + vertex2.Z) / 2.0;

            int i = this->AddVertex(middleX, middleY, middleZ);

            this->middlePointIndexCache[key] = i;
        }
        return this->middlePointIndexCache[key];
    }

    void Mesh::tessellateEdge(size_t v1, size_t v2, size_t n)
    {
        std::pair<size_t, size_t> key;
        if(v1 <= v2)
        {
            key = {v1, v2};
        }
        else
        {
            key= {v2, v1};
        }

        if(this->tessellationPointCache.find(key) == this->tessellationPointCache.end())
        {
            Vector3 va = this->GetVertex(key.first);
            Vector3 vb = this->GetVertex(key.second);
            Vector3 d = (vb - va);

            for (size_t i = 1; i < n; ++i)
            {
                float s = static_cast<float>(i) / static_cast<float>(n);
                Vector3 v = va + d * s;
                this->tessellationPointCache[key].push_back(this->AddVertex(v.X, v.Y, v.Z));
            }
        }
    }

    void Mesh::Subdivide()
    {
        this->middlePointIndexCache.clear();

        for(TriangleIndices tri : this->triangles)
        {
            size_t v0 = this->AddMiddlePoint(tri.V0, tri.V1);
            size_t v1 = this->AddMiddlePoint(tri.V1, tri.V2);
            size_t v2 = this->AddMiddlePoint(tri.V2, tri.V0);

            this->newTris.push_back({tri.V0, v0, v2});
            this->newTris.push_back({tri.V1, v1, v0});
            this->newTris.push_back({tri.V2, v2, v1});
            this->newTris.push_back({v0, v1, v2});
        }
        this->SetTriangles(this->newTris);
        this->newTris.clear();
    }

    void Mesh::Subdivide(int n)
    {
        int i = 0;
        while(i < n)
        {
            this->Subdivide();
            ++i;
        }
    }

    void Mesh::Tessellate(int n)
    {
        std::cout << "Tesellate: " << n << "\n";
    }

    void Mesh::Displace(DisplacementFunction fun, float amp, DisplacementTypeEnum displacementType)
    {
        for(size_t id = 0; id < this->VertexCount(); ++id)
        {
            Vector3 t;

            switch(displacementType)
            {
            case DisplacementTypeEnum::Vertex:
                t = this->GetVertex(id);
                break;
            case DisplacementTypeEnum::Normal:
                t = this->GetNormal(id);
                break;
            default:
                break;
            }

            t *= amp * fun(this->GetVertex(id));
            this->TranslateVertex(id, t);
        }
    }
}
