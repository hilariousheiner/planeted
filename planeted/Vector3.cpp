#include "Vector3.h"

#include <cmath>

#define square(x) x*x

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

    float Vector3::Magnitude()
    {
        return sqrt(this->sqrMagnitude());
    }

    float Vector3::sqrMagnitude()
    {
        return square(this->x) + square(this->y) + square(this->z);
    }

    void Vector3::Normalize()
    {
        float m = this->Magnitude();

        this->x = this->x / m;
        this->y = this->y / m;
        this->z = this->z / m;
    }
}
