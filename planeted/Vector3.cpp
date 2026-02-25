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

    float Vector3::X()
    {
        return this->x;
    }
    float Vector3::Y()
    {
        return this->y;
    }
    float Vector3::Z()
    {
        return this->z;
    }

    void Vector3::Scale(float scalar)
    {
        this->x = this->x * scalar;
        this->y = this->y * scalar;
        this->z = this->z * scalar;
    }

    float Vector3::Magnitude()
    {
        return sqrt(this->SquareMagnitude());
    }

    float Vector3::SquareMagnitude()
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
