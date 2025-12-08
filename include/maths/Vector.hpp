/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Vector.hpp
*/

#pragma once

    #include <iostream>

namespace te {
namespace mat {

enum axe {
    X,
    Y,
    Z
};

class Vector2f {
    public:
        Vector2f() = default;
        Vector2f(float x, float y);
        Vector2f(const Vector2f& vect);
        Vector2f(Vector2f&& vect);
        ~Vector2f() = default;

        Vector2f operator+(const Vector2f &vect) const;
        void operator+=(const Vector2f &vect);
        Vector2f operator-(const Vector2f &vect) const;
        void operator-=(const Vector2f &vect);
        Vector2f operator*(const Vector2f &vect) const;
        void operator*=(const Vector2f &vect);
        Vector2f operator/(const Vector2f &vect) const;
        void operator/=(const Vector2f &vect);
        Vector2f operator+(float x) const;
        void operator+=(float x);
        Vector2f operator*(float x) const;
        void operator*=(float x);
        Vector2f operator/(float x) const;
        void operator/=(float x);

        float x = 0;
        float y = 0;
    private:
};

Vector2f operator-(const Vector2f&);

static inline std::ostream& operator<<(std::ostream& os, const Vector2f& vector)
{
    return os << vector.x << " " << vector.y;
}

}  // namespace mat
}  // namespace te
