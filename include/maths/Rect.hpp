/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Rect.hpp
*/

#pragma once

    #include "maths/Vector.hpp"

namespace te {
namespace mat {

struct RectF {
    RectF(const Vector2f& position, const Vector2f& size);
    RectF(float left, float top, float width, float height);
    RectF(const RectF& other);
    RectF(RectF&& other);

    Vector2f position;
    Vector2f size;
};

} // namespace mat
}  // namespace te

