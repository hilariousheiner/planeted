#include "Vector2.h"

namespace Planeted
{
    Vector2 Vector2::operator*(float scalar) const
    {
        return
        {
            this->X * scalar,
            this->Y * scalar
        };
    }
}
