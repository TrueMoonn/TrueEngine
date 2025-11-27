/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** hitbox.hpp
*/

#pragma once

    #include <SFML/Graphics/Rect.hpp>

namespace te {

struct Hitbox : public sf::FloatRect {
    explicit Hitbox(const sf::FloatRect&);
    Hitbox(const sf::Vector2f&, const sf::Vector2f&);
    Hitbox(float left, float top, float width, float height);
};

}  // namespace te
