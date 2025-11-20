/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** position.hpp
*/

#pragma once

    #include <iostream>
    #include <SFML/System/Vector2.hpp>
    #include <SFML/System/Vector3.hpp>

namespace te {

struct Position2 : public sf::Vector2f {
    Position2() = default;
    Position2(float value_x, float value_y);
    explicit Position2(const sf::Vector2f&);
};

struct Position3 : public sf::Vector3f {
    Position3() = default;
    Position3(float value_x, float value_y, float value_z);
    explicit Position3(const sf::Vector3f&);
};

}  // namespace te
