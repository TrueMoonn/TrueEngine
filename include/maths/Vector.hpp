/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Vector.hpp
*/

#pragma once

    #include <cmath>
#include <cstdlib>
#include <iostream>
    #include <utility>

    #include "maths/numeric.hpp"

namespace mat {

enum axis {
    X = 0,
    Y
};

template <typename Numeric>
    requires arithmetic<Numeric>
struct Vector2 {
    Vector2() = default;
    Vector2(Numeric x, Numeric y) : x(x), y(y) {}
    Vector2(const Vector2& vect) = default;
    Vector2(Vector2&& vect) = default;
    Vector2& operator=(const Vector2&) = default;
    Vector2& operator=(Vector2&&) = default;
    ~Vector2() = default;

    Vector2 operator+(const Vector2 &vect) const {
        return Vector2(this->x + vect.x, this->y + vect.y);
    }
    void operator+=(const Vector2 &vect) {
        this->x += vect.x;
        this->y += vect.y;
    }
    Vector2 operator-(const Vector2 &vect) const {
        return Vector2(this->x - vect.x, this->y - vect.y);
    }
    void operator-=(const Vector2 &vect) {
        this->x -= vect.x;
        this->y -= vect.y;
    }
    Vector2 operator*(const Vector2 &vect) const {
        return Vector2(this->x * vect.x, this->y * vect.y);
    }
    void operator*=(const Vector2 &vect) {
        this->x *= vect.x;
        this->y *= vect.y;
    }
    Vector2 operator/(const Vector2 &vect) const {
        return Vector2(this->x / vect.x, this->y / vect.y);
    }
    void operator/=(const Vector2 &vect) {
        this->x /= vect.x;
        this->y /= vect.y;
    }
    Vector2 operator+(Numeric val) const {
        return Vector2(this->x + val, this->y + val);
    }
    void operator+=(Numeric val) {
        this->x += val;
        this->y += val;
    }
    Vector2 operator*(Numeric val) const {
        return Vector2(this->x * val, this->y * val);
    }
    void operator*=(Numeric val) {
        this->x *= val;
        this->y *= val;
    }
    Vector2 operator/(Numeric val) const {
        return Vector2(this->x / val, this->y / val);
    }
    void operator/=(Numeric val) {
        this->x /= val;
        this->y /= val;
    }

    void normalize(void) {
        int length = sqrt(this->x * this->x + this->y * this->y);

        this->x /= length;
        this->y /= length;
    }

    int distance(Vector2 Vec) {
        return (std::sqrt(pow(abs(this->y - Vec.y), 2)
            + pow(abs(this->y - Vec.x), 2)));
    }

    int length(void) {
        return (sqrt(pow(this->x, 2) + pow(this->y, 2)));
    }

    Numeric x = 0;
    Numeric y = 0;
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<unsigned int> Vector2u;

}  // namespace mat
