#ifndef PLANETED_ICOSPHERE_H
#define PLANETED_ICOSPHERE_H

#include "PlOb.h"
#include "Mesh.h"
#include "Icosahedron.h"

namespace Planeted
{
    class IcoSphere : public PlOb
    {
    private:
        Mesh *mesh;
    public:
        IcoSphere()
        {
            this->mesh = makeIcosahedron();
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
