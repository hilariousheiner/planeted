#include "Vector3.h"

namespace Planeted
{
    Vector3::Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float Vector3::GetX()
    {
        return this->x;
    }
    float Vector3::GetY()
    {
        return this->y;
    }
    float Vector3::GetZ()
    {
        return this->z;
    }
}
