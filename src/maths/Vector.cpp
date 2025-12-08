/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Vector.cpp
*/

#include <cmath>

#include "maths/Vector.hpp"

namespace te {
namespace mat {

Vector2f::Vector2f(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2f::Vector2f(const Vector2f& vect) : x(vect.x), y(vect.y) {}

Vector2f::Vector2f(Vector2f&& vect) :
    x(std::move(vect.x)), y(std::move(vect.y)) {}

Vector2f Vector2f::operator+(const Vector2f &vect) const
{
    return Vector2f(this->x + vect.x, this->y + vect.y);
}

void Vector2f::operator+=(const Vector2f &vect)
{
    this->x += vect.x;
    this->y += vect.y;
}

Vector2f Vector2f::operator-(const Vector2f &vect) const
{
    return Vector2f(this->x - vect.x, this->y - vect.y);
}

void Vector2f::operator-=(const Vector2f &vect)
{
    this->x -= vect.x;
    this->y -= vect.y;
}

Vector2f Vector2f::operator*(const Vector2f &vect) const
{
    return Vector2f(this->x * vect.x, this->y * vect.y);
}

void Vector2f::operator*=(const Vector2f &vect)
{
    this->x *= vect.x;
    this->y *= vect.y;
}

Vector2f Vector2f::operator/(const Vector2f &vect) const
{
    return Vector2f(this->x / vect.x, this->y / vect.y);
}

void Vector2f::operator/=(const Vector2f &vect)
{
    this->x /= vect.x;
    this->y /= vect.y;
}

Vector2f Vector2f::operator+(float x) const
{
    return Vector2f(this->x + x, this->y + y);
}

void Vector2f::operator+=(float x)
{
    this->x += x;
    this->y += x;
}

Vector2f Vector2f::operator*(float x) const
{
    return Vector2f(this->x * x, this->y * y);
}

void Vector2f::operator*=(float x)
{
    this->x *= x;
    this->y *= y;
}

Vector2f Vector2f::operator/(float x) const
{
    return Vector2f(this->x / x, this->y / y);
}

void Vector2f::operator/=(float x)
{
    this->x /= x;
    this->y /= y;
}

Vector2f operator-(const Vector2f& vect)
{
    return Vector2f(-vect.x, -vect.y);
}

}  // mat
}  // te
