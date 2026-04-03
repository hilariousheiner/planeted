#include "Vector3.h"

#include <cmath>

#define square(x) x*x

namespace Planeted
{
    Vector3::Vector3()
    {
        this->X = 0.0f;
        this->Y = 0.0f;
        this->Z = 0.0f;
    }

    Vector3::Vector3(float x, float y, float z)
    {
        this->X = x;
        this->Y = y;
        this->Z = z;
    }

    Vector3 Vector3::operator*(float scalar) const
    {
        return
        {
            this->X * scalar,
            this->Y * scalar,
            this->Z * scalar
        };
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return
        {
            this->X - other.X,
            this->Y - other.Y,
            this->Z - other.Z
        };
    }

    Vector3 Vector3::Cross(const Vector3& other) const
    {
        return
        {
            this->Y * other.Z - this->Z * other.Y,
            this->Z * other.X - this->X * other.Z,
            this->X * other.Y - this->Y * other.X
        };
    }

    Vector3& Vector3::operator*=(float scalar)
    {
        this->X *= scalar;
        this->Y *= scalar;
        this->Z *= scalar;
        return *this;
    }

    Vector3& Vector3::operator+=(const Vector3& other)
    {
        this->X += other.X;
        this->Y += other.Y;
        this->Z += other.Z;
        return *this;
    }

    float Vector3::Magnitude() const
    {
        return sqrt(this->SquareMagnitude());
    }

    float Vector3::SquareMagnitude() const
    {
        return square(this->X) + square(this->Y) + square(this->Z);
    }

    void Vector3::Normalize()
    {
        float m = this->Magnitude();

        this->X = this->X / m;
        this->Y = this->Y / m;
        this->Z = this->Z / m;
    }
}
