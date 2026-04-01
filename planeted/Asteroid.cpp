#include "Asteroid.h"

namespace Planeted
{
    Asteroid::Asteroid()
    {
        this->mesh = MakeIcosphere(4);

        for(int id = 0; id < this->mesh->VertexCount(); ++id)
        {
            Vector3 *vertex = this->mesh->GetVertex(id);
            float scalar = fbm(*vertex);
            *vertex *= scalar;
        }
        this->mesh->CalculateNormals(NormalTypeEnum::PerVertex);
    }

    Asteroid::~Asteroid()
    {
        delete this->mesh;
    }

    Mesh& Asteroid::GenerateMesh()
    {
        return *(this->mesh);
    }
}
