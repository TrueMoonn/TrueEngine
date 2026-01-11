/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** window.cpp
*/

#include <memory>
#include <utility>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "maths/Vector.hpp"
#include "sfml/components/window.hpp"

namespace addon {
namespace sfml {

Window::Window(const std::string& winName, const mat::Vector2u& size,
    std::size_t framerate, bool fs) : name(winName), framerate(framerate) {
    if (fs) {
        win = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(), name, sf::Style::Default, sf::State::Fullscreen);
    } else {
        win = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(sf::Vector2u(size.x, size.y)),
            name);
    }
    win->setFramerateLimit(framerate);
    win->setKeyRepeatEnabled(false);
}

PLUGIN_API void Window::push_back(const Sprite& sp) {
    if (draws.size() <= sp.layer) {
        draws.resize(sp.layer + 1);
    }
    draws[sp.layer].push_back(sp);
}

}  // namespace sfml
}  // namespace addon
