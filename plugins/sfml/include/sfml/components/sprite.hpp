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

struct Sprite {
    Sprite(sf::Texture& texture, std::size_t layer,
        const sf::Vector2f& scale = {1.f, 1.f});
    Sprite(sf::Texture& texture, std::size_t layer,
        const sf::Vector2i& size, const sf::Vector2f& scale = {1.f, 1.f});
    Sprite(const Sprite&) = default;
    Sprite(Sprite&&) noexcept = default;

    sf::Sprite sp;
    std::size_t layer;
};
}  // namespace sfml
}  // namespace addon
