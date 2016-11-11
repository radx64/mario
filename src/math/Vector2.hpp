#ifndef MATH_VECTOR2_HPP
#define MATH_VECTOR2_HPP

#include <cstdint>

namespace math
{

template <typename T>
struct Vector2
{
    T x;
    T y;

    Vector2 operator+(const Vector2& v)
    {
        return Vector2{x+v.x, y+v.y};
    }

    void operator+=(const Vector2& v)
    {
        x+=v.x;
        y+=v.y;
    }

    Vector2 operator-(const Vector2& v)
    {
        return Vector2{x-v.x, y-v.y};
    }

    void operator-=(const Vector2& v)
    {
        x-=v.x;
        y-=v.y;
    }

    Vector2 operator*(const Vector2& v)
    {
        return Vector2{x*v.x, y*v.y};
    }

    Vector2 operator/(const Vector2& v)
    {
        return Vector2{x/v.x, y.v.y};
    }

    Vector2 operator*(const double d)
    {
        return Vector2{x*d, y*d};
    }

    Vector2 operator/(const double d)
    {
        return Vector2{x/d, y/d};
    }

};

using Vector2i = Vector2<uint32_t>;
using Vector2f = Vector2<double>;

}  // namespace math

#endif  // MATH_VECTOR2_HPP