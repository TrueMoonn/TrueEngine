/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** sprite.hpp
*/

#pragma once

    #include <SFML/Graphics/Sprite.hpp>
    #include <SFML/Graphics/Texture.hpp>
    #include <SFML/System/Vector2.hpp>

namespace addon {
namespace sfml {

struct Sprite {
    Sprite(sf::Texture& texture, std::size_t layer,
        const sf::Vector2f& scale = {1.f, 1.f},
        const sf::Vector2f& origin = {0.f, 0.f});
    Sprite(sf::Texture& texture, std::size_t layer,
        const sf::Vector2i& size, const sf::Vector2f& scale = {1.f, 1.f},
        const sf::Vector2f& origin = {0.f, 0.f});
    Sprite(const Sprite&) = default;
    Sprite(Sprite&&) noexcept = default;
    Sprite& operator=(const Sprite& other) = default;
    Sprite& operator=(Sprite&& other) noexcept = default;

    sf::Sprite sp;
    std::size_t layer;
};
}  // namespace sfml
}  // namespace addon
