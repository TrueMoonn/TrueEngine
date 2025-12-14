/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** sprite.cpp
*/

#include <SFML/Graphics/Texture.hpp>

#include "sfml/components/sprite.hpp"

namespace addon {
namespace sfml {

Sprite::Sprite(sf::Texture& texture, std::size_t layer,
    const sf::Vector2f& scale) : layer(layer), sp(texture) {
    sp.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(texture.getSize())));
    sp.setScale(scale);
}

Sprite::Sprite(sf::Texture& texture, std::size_t layer,
    const sf::Vector2i &size, const sf::Vector2f &scale) :
    layer(layer), sp(texture) {
    sp.setTextureRect(sf::IntRect({0, 0}, size));
    sp.setScale(scale);
}

}  // namespace sfml
}  // namespace addon
