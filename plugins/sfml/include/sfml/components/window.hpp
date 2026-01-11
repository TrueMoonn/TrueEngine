/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** window.hpp
*/

#pragma once

    #include <vector>
    #include <memory>
    #include <string>
    #include <SFML/Graphics/RenderWindow.hpp>
    #include <SFML/Window/VideoMode.hpp>

    #include "plugin/plugin_api.hpp"
    #include "maths/Vector.hpp"
    #include "sfml/components/sprite.hpp"

namespace addon {
namespace sfml {

#define DEFAULT_FRAME_LIMIT 60
#define DEFAULT_WIN_NAME "TE-game"
#define DEFAULT_WIN_SIZE {1280, 720}

struct PLUGIN_API Window {
    Window(const std::string& name = DEFAULT_WIN_NAME,
        const mat::Vector2u& size = DEFAULT_WIN_SIZE,
        std::size_t framerate = DEFAULT_FRAME_LIMIT,
        bool fullscreen = false);

    Window(const Window& other) :
        name(other.name),
        framerate(other.framerate) {
        win = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(other.win->getSize()),
            other.name);
        win->setFramerateLimit(framerate);
        win->setKeyRepeatEnabled(false);
    }
    Window& operator=(const Window& other) {
        if (this != &other) {
            name = other.name;
            framerate = other.framerate;
            draws = other.draws;
            win = std::make_unique<sf::RenderWindow>(
                sf::VideoMode(other.win->getSize()),
                other.name);
            win->setFramerateLimit(other.framerate);
            win->setKeyRepeatEnabled(false);
        }
        return *this;
    }

    Window(Window&&) noexcept = default;
    Window& operator=(Window&& other) noexcept = default;

    PLUGIN_API void push_back(const Sprite& sp);
    std::vector<std::vector<Sprite>> draws;
    std::unique_ptr<sf::RenderWindow> win;
    std::string name;
    std::size_t framerate;
};

}  // namespace sfml
}  // namespace addon
