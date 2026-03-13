#include "IcoSphere.h"

namespace Planeted
{
    Mesh *MakeIcosphere()
    {
        Mesh *result = MakeIcosahedron();
        MeshSubdivider subdivider(result);

        subdivider.Subdivide();
        subdivider.Subdivide();

        result->ProjectToUnitSphere();

        return result;
    }

    IcoSphere::IcoSphere()
    {
        this->mesh = MakeIcosphere();
    }

    IcoSphere::~IcoSphere()
    {
        delete this->mesh;
    }

    Mesh& IcoSphere::GenerateMesh()
    {
        return *(this->mesh);
    }
}
