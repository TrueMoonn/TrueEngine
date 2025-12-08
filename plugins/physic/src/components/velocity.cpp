/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** velocity.cpp
*/

#include "physic/components/velocity.hpp"

namespace te {

Velocity2::Velocity2(float value_x, float value_y) :
mat::Vector2f(value_x, value_y)
{}

Velocity2::Velocity2(const mat::Vector2f& vect) : mat::Vector2f(vect) {}

// Velocity3::Velocity3(float value_x, float value_y, float value_z) :
// sf::Vector3f(value_x, value_y, value_z)
// {}

// Velocity3::Velocity3(const sf::Vector3f& vect) :
// sf::Vector3f(vect)
// {}

}  // namespace te
