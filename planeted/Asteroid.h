#ifndef PLANETED_ASTEROID_H
#define PLANETED_ASTEROID_H

#include "PlOb.h"
#include "Mesh.h"
#include "IcoSphere.h"
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
