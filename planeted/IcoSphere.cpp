#include "IcoSphere.h"

namespace Planeted
{
    Mesh *MakeIcosphere(std::string name, int d)
    {
        Mesh *result = MakeIcosahedron(name);
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

    /*
    IcoSphere::IcoSphere(std::string name)
    {
        this->mesh = MakeIcosphere(name, 2);
    }

    IcoSphere::~IcoSphere()
    {
        delete this->mesh;
    }

    Mesh& IcoSphere::GenerateMesh()
    {
        return *(this->mesh);
    }*/
}
