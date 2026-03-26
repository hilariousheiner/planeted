#ifndef PLANETED_MATH_H
#define PLANETED_MATH_H

namespace Planeted
{
    template <typename T>
    inline T Clamp(const T &value, const T &minVal, const T &maxVal)
    {
        return std::max(minVal, std::min(maxVal, value));
    }

    template <typename T>
    inline T Clamp01(const T &value)
    {
        return Clamp(value, static_cast<T>(0), static_cast<T>(1));
    }

    template <typename T, typename U>
    inline T Lerp(const T &a, const T &b, const U &t)
    {
        return a + (b - a) * Clamp01(t);
    }

    template <typename T, typename U>
    inline T LerpUnclamped(const T &a, const T &b, const U &t)
    {
        return a + (b - a) * t;
    }

    template <typename T, typename U>
    inline T SmoothStep(const T &a, const T &b, const U &t)
    {
        U x = Clamp01(t);
        x = x * x * (static_cast<U>(3) - static_cast<U>(2) * x);
        return LerpUnclamped(a, b, x);
    }

    template <typename T, typename U>
    inline T SmoothStepUnclamped(const T &a, const T &b, const U &t)
    {
        U x = t * t * (static_cast<U>(3) - static_cast<U>(2) * t);
        return LerpUnclamped(a, b, x);
    }

    inline int FloorToInt(const float &value)
    {
        int i = static_cast<int>(value);
        return (value < 0 && value != i) ? i - 1 : i;
    }
}
#endif // PLANETED_MATH_H
