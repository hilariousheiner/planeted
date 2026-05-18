#include "Mesh.h"
#include <stdexcept>

namespace Planeted
{
    Mesh::Mesh()
      : name("mesh"), normalType(NormalTypeEnum::None)
    {}

    Mesh::Mesh(std::string name)
        : name(name), normalType(NormalTypeEnum::None)
    {}

    int Mesh::AddVertex(float x, float y, float z)
    {
        int result = this->vertices.size();

        this->vertices.push_back(Vector3 {x, y, z});

        return result;
    }

    const Vector3 &Mesh::GetVertex(size_t id) const
    {
        if(id >= this->vertices.size())
        {
            throw std::out_of_range("Index out of bounds");
        }
        return this->vertices[id];
    }

    Vector3 *Mesh::GetVertex(size_t id)
    {
        if(id >= this->vertices.size())
        {
            throw std::out_of_range("Index out of bounds");
        }
        return &this->vertices[id];
    }

    const Vector3 &Mesh::GetNormal(size_t id) const
    {
        if(id >= this->normals.size())
        {
            throw std::out_of_range("Index out of bounds");
        }
        return this->normals[id];
    }

    void Mesh::AddTriangle(int a, int b, int c)
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

    int Mesh::VertexCount() const
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

    NormalTypeEnum Mesh::GetNormalType() const
    {
        return this->normalType;
    }

    int addNormal(Vector3 n, std::vector<Vector3> &normals);
    inline Vector3 calculateNormal(TriangleIndices i, std::vector<Vector3> &vertices);

    void Mesh::CalculateNormals(NormalTypeEnum normalType)
    {
        this->normalType = normalType;

        switch(normalType)
        {
            case NormalTypeEnum::PerFace:

                this->normals.resize(this->triangles.size());

                for(TriangleIndices &i : this->triangles)
                {
                    Vector3 normal = calculateNormal(i, this->vertices);
                    i.N = addNormal(normal, this->normals);
                }
                break;
            case NormalTypeEnum::PerVertex:

                this->normals.resize(this->vertices.size());

                for(TriangleIndices &i : this->triangles)
                {
                    Vector3 normal = calculateNormal(i, this->vertices);

                    this->normals[i.V0] += normal;
                    this->normals[i.V1] += normal;
                    this->normals[i.V2] += normal;
                }

                break;
            case NormalTypeEnum::None:
            default:
                this->normals.clear();
                break;
        }

        for(Vector3 &normal : this->normals)
        {
            normal.Normalize();
        }
    }

    inline Vector3 calculateNormal(TriangleIndices i, std::vector<Vector3> &vertices)
    {
        const Vector3 &v0 = vertices[i.V0];
        const Vector3 &v1 = vertices[i.V1];
        const Vector3 &v2 = vertices[i.V2];

        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;

        Vector3 normal = edge1.Cross(edge2);

        return normal;
    }

    int addNormal(Vector3 n, std::vector<Vector3> &normals)
    {
        int result = normals.size();

        normals.push_back(n);

        return result;
    }

    const std::string &Mesh::GetName() const
    {
        return this->name;
    }
}
