/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** sound.hpp
*/

#pragma once

    #include <SFML/Graphics/Text.hpp>
    #include <SFML/Graphics/Font.hpp>
    #include <SFML/System/Vector2.hpp>

namespace addon {
namespace sfml {

struct Text {
    Text(std::string str, sf::Font font,
        sf::Text::Style style, sf::Color color, std::size_t size);
    Text(const Text& other) = default;
    Text(Text&&) noexcept = default;

    sf::Font font;
    sf::Text text;
    sf::Text::Style style;
    sf::Color color;
    std::size_t size;
    sf::Vector2i pos;
};
}  // namespace sfml
}  // namespace addon
