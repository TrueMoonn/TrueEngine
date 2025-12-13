/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** sprite.hpp
*/

#pragma once

    #include <SFML/Graphics/Sprite.hpp>
    #include <SFML/Graphics/Texture.hpp>

namespace addon {
namespace sfml {

struct Sprite : public sf::Sprite {
    explicit Sprite(sf::Texture&& text,
        const sf::Vector2f& scale = {1.f, 1.f});
    Sprite(sf::Texture&& text, const sf::Vector2i& size,
        const sf::Vector2f& scale = {1.f, 1.f});
    Sprite(const Sprite& other);
    Sprite(Sprite&& other) noexcept;
    const sf::Texture texture;
};
}  // namespace sfml
}  // namespace addon
