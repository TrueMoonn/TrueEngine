/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** sprite.hpp
*/

#pragma once

    #include <iostream>
    #include <SFML/Graphics/Sprite.hpp>
    #include <SFML/Graphics/Texture.hpp>

namespace te {

struct Sprite : public sf::Sprite {
    explicit Sprite(sf::Texture&& text, const sf::Vector2f& scale = {1.f, 1.f}) : texture(std::move(text)), sf::Sprite(texture) {
        setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(texture.getSize())));
        setScale(scale);
    }
    Sprite(const Sprite& other) : texture(other.texture), sf::Sprite(texture) {}
    Sprite(Sprite&& other) noexcept : texture(std::move(other.texture)), sf::Sprite(texture) {
        setTextureRect(other.getTextureRect());
    }
    const sf::Texture texture;
};

}  // namespace te
