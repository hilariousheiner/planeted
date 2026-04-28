#ifndef PLANETED_VECTOR2_H
#define PLANETED_VECTOR2_H

namespace Planeted
{
    struct Vector2
    {
        float X;
        float Y;

        Vector2 operator*(float scalar) const;
    };
}
#endif
