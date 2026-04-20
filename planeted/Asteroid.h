#ifndef PLANETED_ASTEROID_H
#define PLANETED_ASTEROID_H

#include <string>

#include "IcoSphere.h"
#include "Mesh.h"
#include "PlOb.h"
#include "Random.h"

namespace Planeted
{
    class Asteroid : public PlOb
    {
    public:
        Asteroid(std::string name);
        ~Asteroid() override;

        Mesh& GenerateMesh() override;
    private:
        Mesh *mesh;
    };
}
#endif // PLANETED_ASTEROID_H
