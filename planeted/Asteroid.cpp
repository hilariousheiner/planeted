#include "Asteroid.h"

namespace Planeted
{
    Asteroid::Asteroid()
    {
        this->mesh = MakeIcosphere(4);

        for(int id = 0; id < this->mesh->VertexCount(); ++id)
        {
            Vector3 *vertex = this->mesh->GetVertex(id);
            float scalar = ValueNoise::GetValue(*vertex) + Random::Range(0.0f, 0.1f);
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
