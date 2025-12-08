/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** hitbox.cpp
*/

#include "physic/components/hitbox.hpp"

namespace te {

Hitbox::Hitbox(const mat::Vector2f& pos, const mat::Vector2f& size) {
    this->size.y = size.y;
    this->size.x = size.x;
    this->position.y = pos.y;
    this->position.x = pos.x;
}

Hitbox::Hitbox(float left, float top, float width, float height) {
    this->size.y = height;
    this->size.x = width;
    this->position.y = top;
    this->position.x = left;
}

}  // namespace te
