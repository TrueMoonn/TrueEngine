/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** window.cpp
*/

#include <utility>

#include "display/components/window.hpp"

namespace te {

Window::Window() : sf::RenderWindow(DEFAULT_VIDEO_MODE, DEFAULT_WIN_NAME) {
    setFramerateLimit(DEFAULT_FRAME_LIMIT);
    name = DEFAULT_WIN_NAME;
}

Window::Window(const Window& win): sf::RenderWindow(sf::VideoMode(
    sf::Vector2u(win.getSize().x, win.getSize().y)), win.name) {
    setFramerateLimit(DEFAULT_FRAME_LIMIT);
    name = win.name;
}

Window::Window(Window&& win) : sf::RenderWindow(std::move(win)),
    name(std::move(win.name)) {
    setFramerateLimit(DEFAULT_FRAME_LIMIT);
}

}  // namespace te
