#include "Mesh.h"
#include <stdexcept>

namespace Planeted
{
    int Mesh::AddVertex(float x, float y, float z)
    {
        int result = this->vertices.size();

        this->vertices.push_back(Vector3 {x, y, z});

        return result;
    }

    Vector3 *Mesh::GetVertex(size_t id)
    {
        if(id >= this->vertices.size())
        {
            throw std::out_of_range("Index out of bounds");
        }
        return &this->vertices[id];
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
            this->AddTriangle(tri.v0, tri.v1, tri.v2);
        }
    }

    int Mesh::VertexCount()
    {
        return this->vertices.size();
    }
    int Mesh::TriangleCount()
    {
        return this->triangles.size();
    }

    VectorIterator Mesh::Vertices() const
    {
        return {this->vertices.begin(), this->vertices.end()};
    }

    VectorIterator Mesh::Normals() const
    {
        return {this->normals.begin(), this->normals.end()};
    }

    TriangleIterator Mesh::Triangles() const
    {
        return {this->triangles.begin(), this->triangles.end()};
    }

    void Mesh::ProjectToUnitSphere()
    {
        for(Vector3& v : this->vertices)
        {
            v.Normalize();
        }
    }

    int addNormal(Vector3 n, std::vector<Vector3>& normals);
    inline Vector3 calculateNormal(TriangleIndices i, std::vector<Vector3>& vertices);

    void Mesh::CalculateNormals()
    {
        for(TriangleIndices& i : this->triangles)
        {
            Vector3 normal = calculateNormal(i, this->vertices);
            i.n = addNormal(normal, this->normals);
        }
    }

    inline Vector3 calculateNormal(TriangleIndices i, std::vector<Vector3>& vertices)
    {
        const Vector3& v0 = vertices[i.v0];
        const Vector3& v1 = vertices[i.v1];
        const Vector3& v2 = vertices[i.v2];

        Vector3 edge1 = v1 - v0;
        Vector3 edge2 = v2 - v0;

        Vector3 normal = edge1.Cross(edge2);

        normal.Normalize();

        return normal;
    }

    int addNormal(Vector3 n, std::vector<Vector3>& normals)
    {
        int result = normals.size();

        normals.push_back(n);

        return result;
    }
}
