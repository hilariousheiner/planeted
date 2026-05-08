#include "Asteroid.h"

namespace Planeted
{
    Asteroid::Asteroid(std::string name)
    {
        this->mesh = MakeIcosphere(name, 4);

        for(int id = 0; id < this->mesh->VertexCount(); ++id)
        {
            Vector3 *vertex = this->mesh->GetVertex(id);
            float scalar = 1 + 0.25 * Random::GradientNoiseFBM(*vertex);
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
