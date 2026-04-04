#ifndef PLANETED_COLOR_H
#define PLANETED_COLOR_H

#include <cmath> // for std::round
#include <cstdint>

#include "Math.h" // for Clamp01

namespace Planeted
{
    struct Color
    {
        std::uint8_t R;
        std::uint8_t G;
        std::uint8_t B;
    };


    inline std::uint8_t ToUint8(float x)
    {
        x = Clamp01(x);
        return static_cast<std::uint8_t>(std::round(x * 255.0f));
    }

    namespace Colors
    {
        static constexpr Color Black {0  ,   0,   0};
        static constexpr Color Red   {255,   0,   0};
        static constexpr Color Green {0  , 255,   0};
        static constexpr Color Blue  {0  ,   0, 255};
        static constexpr Color White {255, 255, 255};
    }
}
#endif // PLANETED_COLOR_H

