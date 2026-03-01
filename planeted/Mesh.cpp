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
            this->AddTriangle(tri.a, tri.b, tri.c);
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

    VertexIterator Mesh::Vertices() const
    {
        return {this->vertices.begin(), this->vertices.end()};
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
}
