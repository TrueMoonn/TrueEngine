/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** interactive.hpp
*/

#pragma once

    #include <functional>

    #include <SFML/Graphics/Rect.hpp>

    #include "Registry.hpp"

namespace te {

typedef std::function<void(ECS::Registry&)> interactive_func;

struct Interactive {
    Interactive(const sf::FloatRect&,
        const interactive_func& func = [](ECS::Registry&){});
    Interactive(const sf::Vector2f&, const sf::Vector2f&,
        const interactive_func& func = [](ECS::Registry&){});
    Interactive(float left, float top, float width, float height,
        const interactive_func& func = [](ECS::Registry&){});
    sf::FloatRect hitbox;
    interactive_func event;
};

}  // namespace te
