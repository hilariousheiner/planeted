#ifndef PLANETED_ASTEROID_H
#define PLANETED_ASTEROID_H

#include "IcoSphere.h"
#include "Mesh.h"
#include "PlOb.h"
#include "Random.h"

namespace Planeted
{
    class Asteroid : public PlOb
    {
    public:
        Asteroid();
        ~Asteroid() override;

        Mesh& GenerateMesh() override;
    private:
        Mesh *mesh;
    };
}
#endif // PLANETED_ASTEROID_H
