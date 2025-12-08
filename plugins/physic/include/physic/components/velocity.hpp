/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** velocity.hpp
*/

#pragma once

    #include "maths/Vector.hpp"

namespace te {

struct Velocity2 : public mat::Vector2f {
    Velocity2() = default;
    Velocity2(float value_x, float value_y);
    explicit Velocity2(const mat::Vector2f&);
};

}  // namespace te
