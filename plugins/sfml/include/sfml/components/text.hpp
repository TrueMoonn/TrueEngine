/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** sprite.hpp
*/

#pragma once

    #include <string>

    #include <SFML/Graphics/Font.hpp>
    #include <SFML/Graphics/Text.hpp>
    #include <SFML/Graphics/Color.hpp>

    #include <maths/Vector.hpp>

    #include "plugin/plugin_api.hpp"

namespace addon {
namespace sfml {

/**
 * @brief Text component for the sfml plugin
 *
 * @param font : the path of the font to use
 * @param str : the text string
 * @param offset : the offset from the entity's position
 * @param center : weither the text will be centered on it's position or not
 * @param size : the character size
 * @param color : the text's color as a 4 value code.
 */
struct PLUGIN_API Text : sf::Text {
    Text(const sf::Font &font, const std::string &str
        , const mat::Vector2i &offset, bool center = false
        , std::size_t size = 30 , const sf::Color &color = sf::Color::Black);

    std::string str;
    std::size_t charSize;
    mat::Vector2i offset;
    sf::Color color;
    bool center;
};

}  // namespace sfml
}  // namespace addon
