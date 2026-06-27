#ifndef PLANETED_VECTOR3_H
#define PLANETED_VECTOR3_H

namespace Planeted
{
    struct Vector3
    {
        float X;
        float Y;
        float Z;

        Vector3();
        Vector3(float x, float y, float z);

        Vector3 operator-(const Vector3& other) const;
        Vector3& operator*=(float scalar);
        Vector3& operator+=(const Vector3& other);

        Vector3 Cross(const Vector3& other) const;

        float Magnitude() const;
        float SquareMagnitude() const;
        void Normalize();
    };

    inline Vector3 operator*(Vector3 lhs, float scalar)
    {
        lhs *= scalar;
        return lhs;
    }

    inline Vector3 operator*(float scalar, Vector3 rhs)
    {
        return rhs * scalar;
    }

    inline Vector3 operator+(Vector3 lhs, Vector3 rhs)
    {
        lhs += rhs;
        return lhs;
    }
}
#endif
