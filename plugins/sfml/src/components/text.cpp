/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** text.cpp
*/

#include "sfml/components/text.hpp"

namespace addon {
namespace sfml {

Text::Text(std::string str, sf::Font font,
    sf::Text::Style style, sf::Color color, std::size_t size) :
    font(font)
    , style(style)
    , color(color)
    , size(size)
    , text(font, str, size)
{}


}  // namespace sfml
}  // namespace addon
