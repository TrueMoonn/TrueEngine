/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** hitbox.hpp
*/

#pragma once

    #include "maths/Vector.hpp"

namespace addon {
namespace physic {

struct Hitbox {
    Hitbox(const mat::Vector2f& position, const mat::Vector2f& size);
    Hitbox(float left, float top, float width, float height);

    mat::Vector2f position;
    mat::Vector2f size;
};

}  // namespace physic
}  // namespace addon
