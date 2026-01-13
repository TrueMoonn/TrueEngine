/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** sprite.cpp
*/

#include <iostream>
#include <string>

#include <SFML/Graphics/Text.hpp>

#include "sfml/components/text.hpp"

namespace addon {
namespace sfml {

Text::Text(const std::string &fontPath, const std::string &str
    , const mat::Vector2i &offset, std::size_t size, const sf::Color &color)
        : str(str), offset(offset), color(color)
        , font(fontPath), sf::Text(font, str, size) {
            this->setFillColor(color);
            this->setCharacterSize(size);
    }

}  // namespace sfml
}  // namespace addon
