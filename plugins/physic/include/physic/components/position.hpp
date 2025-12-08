/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** position.hpp
*/

#pragma once

    #include <iostream>

    #include "maths/Vector.hpp"

namespace addon {
namespace physic {

struct Position2 : public mat::Vector2f {
    Position2() = default;
    Position2(float value_x, float value_y);
    explicit Position2(const mat::Vector2f&);
};

}  // namespace physic
}  // namespace addon
