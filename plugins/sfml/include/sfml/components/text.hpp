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
 * @param fontpath : the
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
