#ifndef PLANETED_ICOSPHERE_H
#define PLANETED_ICOSPHERE_H

#include "PlOb.h"
#include "Mesh.h"
#include "Icosahedron.h"
#include "MeshSubdivider.h"

namespace Planeted
{
    class IcoSphere : public PlOb
    {
    private:
        Mesh *mesh;
    public:
        IcoSphere()
        {
            this->mesh = MakeIcosahedron();
            MeshSubdivider subdivider(this->mesh);

            subdivider.Subdivide();

            this->mesh->ProjectToUnitSphere();
        }
        ~IcoSphere()
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
