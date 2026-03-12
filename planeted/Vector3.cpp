#include "Vector3.h"

#include <cmath>

#define square(x) x*x

namespace Planeted
{
    Vector3::Vector3()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }

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

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return {this->x - other.x, this->y - other.y, this->z - other.z};
    }

    Vector3 Vector3::Cross(const Vector3& other) const
    {
        return
        {
            this->y * other.z - this->z * other.y,
            this->z * other.x - this->x * other.z,
            this->x * other.y - this->y * other.x
        };
    }

    Vector3& Vector3::operator*=(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }

    Vector3& Vector3::operator+=(const Vector3& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
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
