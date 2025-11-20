/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** sprite.hpp
*/

#pragma once

    #include <SFML/Graphics/Sprite.hpp>
    #include <SFML/Graphics/Texture.hpp>

namespace te {

struct Sprite : public sf::Sprite {
    explicit Sprite(const sf::Texture& texture) : sf::Sprite(texture) {}
};

}  // namespace te
