/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Rect.cpp
*/

#include "maths/Rect.hpp"

namespace te {
namespace mat {

RectF::RectF(const Vector2f& position, const Vector2f& size) :
    position(position), size(size) {}

RectF::RectF(float left, float top, float width, float height) :
    position(left, top), size(width, height) {}

RectF::RectF(const RectF& other) :
    position(other.position), size(other.size) {}

RectF::RectF(RectF&& other) :
    position(std::move(other.position)), size(std::move(other.size)) {}

}  // namespace mat
}  // namespace te
