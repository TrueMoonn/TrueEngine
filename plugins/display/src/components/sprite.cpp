/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** sprite.cpp
*/

#include <utility>

#include "display/components/sprite.hpp"

namespace te {

Sprite::Sprite(sf::Texture&& text, const sf::Vector2f& scale) :
    texture(std::move(text)), sf::Sprite(texture) {
    setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(texture.getSize())));
    setScale(scale);
}

Sprite::Sprite(const Sprite& other) :
    texture(other.texture), sf::Sprite(texture) {}

Sprite::Sprite(Sprite&& other) noexcept :
    texture(std::move(other.texture)), sf::Sprite(texture) {
    setTextureRect(other.getTextureRect());
}

}  // namespace te
