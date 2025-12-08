/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Rect.hpp
*/

#pragma once

    #include <utility>

    #include "maths/Vector.hpp"
    #include "maths/numeric.hpp"

namespace te {
namespace mat {

template <typename Numeric>
    requires arithmetic<Numeric>
struct Rect {
    Rect(const Vector2<Numeric>& position, const Vector2<Numeric>& size) :
        position(position), size(size) {}
    Rect(Numeric left, Numeric top, Numeric width, Numeric height) :
        position(left, top), size(width, height) {}

    Rect(const Rect& other) : position(other.position), size(other.size) {}
    Rect(Rect&& other) :
        position(std::move(other.position)), size(std::move(other.size)) {}

    Vector2<Numeric> position;
    Vector2<Numeric> size;
};

typedef Rect<int> RectI;
typedef Rect<float> RectF;
typedef Rect<unsigned int> RectU;

}  // namespace mat
}  // namespace te

