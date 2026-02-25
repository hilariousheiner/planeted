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
    private:
        Mesh *mesh;

    public:
        Asteroid()
        {
            this->mesh = MakeIcosphere();

            Random random;

            for(int id = 0; id < this->mesh->VertexCount(); ++id)
            {
                Vector3 *vertex = this->mesh->GetVertex(id);
                float scalar = 1.0f + (random.GetValue() * 0.1f);
                vertex->Scale(scalar);
            }
        }
        ~Asteroid()
        {
            delete this->mesh;
        }

        Mesh *GenerateMesh() override
        {
            return this->mesh;
        }
    };
}
#endif // PLANETED_ASTEROID_H
