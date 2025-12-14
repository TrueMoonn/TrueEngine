/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** window.cpp
*/

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
    std::size_t framerate) :
    sf::RenderWindow(sf::VideoMode(sf::Vector2u(size.x, size.y)), winName),
    name(winName),
    framerate(framerate) {
    setFramerateLimit(this->framerate);
}

Window::Window(const Window& win): sf::RenderWindow(sf::VideoMode(
    sf::Vector2u(win.getSize().x, win.getSize().y)), win.name), name(win.name) {
    setFramerateLimit(framerate);
}

Window::Window(Window&& win) : sf::RenderWindow(std::move(win)),
    name(std::move(win.name)), framerate(std::move(win.framerate)) {
    setFramerateLimit(framerate);
}
void Window::push_back(const Sprite& sp) {
    if (draws.size() <= sp.layer) {
        draws.resize(sp.layer + 1);
    }
    draws[sp.layer].push_back(sp);
}

}  // namespace sfml
}  // namespace addon
