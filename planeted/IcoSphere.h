#ifndef PLANETED_ICOSPHERE_H
#define PLANETED_ICOSPHERE_H

#include "PlOb.h"
#include "Mesh.h"
#include "Icosahedron.h"
#include "MeshSubdivider.h"

namespace Planeted
{
    Mesh *MakeIcosphere();

    class IcoSphere : public PlOb
    {
    public:
        IcoSphere();
        ~IcoSphere() override;

        Mesh& GenerateMesh() override;
    private:
        Mesh *mesh;
    };
}
#endif // PLANETED_ICOSPHERE_H
