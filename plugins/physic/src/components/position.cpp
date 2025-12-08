/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** position.cpp
*/

#include "physic/components/position.hpp"

namespace te {

Position2::Position2(float value_x, float value_y) :
    mat::Vector2f(value_x, value_y) {}

Position2::Position2(const mat::Vector2f& vect) : mat::Vector2f(vect) {}

// Position3::Position3(float value_x, float value_y, float value_z):
// sf::Vector3f(value_x, value_y, value_z)
// {}

// Position3::Position3(const sf::Vector3f& vect) :
// sf::Vector3f(vect)
// {}

}  // namespace te
