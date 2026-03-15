#include "IcoSphere.h"

namespace Planeted
{
    Mesh *MakeIcosphere(int d)
    {
        Mesh *result = MakeIcosahedron();
        MeshSubdivider subdivider(result);

        int i = 0;
        while(i < d)
        {
            subdivider.Subdivide();
            ++i;
        }

        result->ProjectToUnitSphere();

        return result;
    }

    IcoSphere::IcoSphere()
    {
        this->mesh = MakeIcosphere(2);
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
