#ifndef PLANETED_ICOSPHERE_H
#define PLANETED_ICOSPHERE_H

#include "PlOb.h"
#include "Mesh.h"
#include "Icosahedron.h"
#include "MeshSubdivider.h"

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

    class IcoSphere : public PlOb
    {
    private:
        Mesh *mesh;
    public:
        IcoSphere()
        {
            this->mesh = MakeIcosphere();
            /*
            this->mesh = MakeIcosahedron();
            MeshSubdivider subdivider(this->mesh);

            subdivider.Subdivide();
            subdivider.Subdivide();

            this->mesh->ProjectToUnitSphere();
            */
        }
        ~IcoSphere() override
        {
            delete this->mesh;
        }

        Mesh *GenerateMesh() override
        {
            return this->mesh;
        }
    };
}
#endif // PLANETED_ICOSPHERE_H
