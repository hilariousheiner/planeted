#include "Mesh.h"

namespace Planeted
{
    Mesh::Mesh()
    {
    }

    Mesh::~Mesh()
    {
    }

    int Mesh::AddVertex(float x, float y, float z)
    {
        int result = this->vertices.size();

        this->vertices.push_back(Vector3 {x, y, z});

        return result;
    }

    void Mesh::AddTriangle(int a, int b, int c)
    {
        this->triangles.push_back(TriangleIndices {a, b, c});
    }

    int Mesh::VertexCount()
    {
        return this->vertices.size();
    }
    int Mesh::TriangleCount()
    {
        return this->triangles.size();
    }

    void Mesh::ProjectToUnitSphere()
    {
        for(Vector3& v : this->vertices)
        {
            v.Normalize();
        }
    }
}
