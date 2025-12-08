/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Vector.hpp
*/

#pragma once

    #include <iostream>
    #include <utility>

    #include "maths/numeric.hpp"

namespace te {
namespace mat {

enum axis {
    X = 0,
    Y
};

template <typename Numeric>
    requires arithmetic<Numeric>
struct Vector2 {
    Vector2() = default;
    Vector2(Numeric x, Numeric y) {
        this->x = x;
        this->y = y;
    }
    Vector2(const Vector2& vect) : x(vect.x), y(vect.y) {}
    Vector2(Vector2&& vect) : x(std::move(vect.x)), y(std::move(vect.y)) {}
    ~Vector2() = default;

    Vector2 operator+(const Vector2 &vect) const {
        return Vector2f(this->x + vect.x, this->y + vect.y);
    }
    void operator+=(const Vector2 &vect) {
        this->x += vect.x;
        this->y += vect.y;
    }
    Vector2 operator-(const Vector2 &vect) const {
        return Vector2f(this->x - vect.x, this->y - vect.y);
    }
    void operator-=(const Vector2 &vect) {
        this->x -= vect.x;
        this->y -= vect.y;
    }
    Vector2 operator*(const Vector2 &vect) const {
        return Vector2f(this->x * vect.x, this->y * vect.y);
    }
    void operator*=(const Vector2 &vect) {
        this->x *= vect.x;
        this->y *= vect.y;
    }
    Vector2 operator/(const Vector2 &vect) const {
        return Vector2f(this->x / vect.x, this->y / vect.y);
    }
    void operator/=(const Vector2 &vect) {
        this->x /= vect.x;
        this->y /= vect.y;
    }
    Vector2 operator+(Numeric x) const {
        return Vector2f(this->x + x, this->y + y);
    }
    void operator+=(Numeric x) {
        this->x += x;
        this->y += x;
    }
    Vector2 operator*(Numeric x) const {
        return Vector2f(this->x * x, this->y * y);
    }
    void operator*=(Numeric x) {
        this->x *= x;
        this->y *= y;
    }
    Vector2 operator/(Numeric x) const {
        return Vector2f(this->x / x, this->y / y);
    }
    void operator/=(Numeric x) {
        this->x /= x;
        this->y /= y;
    }

    Numeric x = 0;
    Numeric y = 0;
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<unsigned int> Vector2u;

}  // namespace mat
}  // namespace te
