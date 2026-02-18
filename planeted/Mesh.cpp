#include "Mesh.h"

namespace Planeted
{
    Mesh::Mesh()
    {
    }

    Mesh::~Mesh()
    {
    }

    Mesh::AddVertex(float x, float y, float z)
    {
        this->vertices.push_back(Vector3 {x, y, z});
    }
}
