#ifndef PLANETED_COLOR_H
#define PLANETED_COLOR_H

#include <cstdint>

namespace Planeted
{
    struct Color
    {
        std::uint8_t R;
        std::uint8_t G;
        std::uint8_t B;
    };

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

