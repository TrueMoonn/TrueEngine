/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** window.hpp
*/

#pragma once

    #include <vector>
    #include <string>
    #include <SFML/Graphics/RenderWindow.hpp>
    #include <SFML/Window/VideoMode.hpp>

    #include "maths/Vector.hpp"
    #include "sfml/components/sprite.hpp"

namespace addon {
namespace sfml {

#define DEFAULT_FRAME_LIMIT 60
#define DEFAULT_WIN_NAME "TE-game"
#define DEFAULT_WIN_SIZE {1280, 720}

struct Window {
    Window(const std::string& name = DEFAULT_WIN_NAME,
        const mat::Vector2u& size = DEFAULT_WIN_SIZE,
        std::size_t framerate = DEFAULT_FRAME_LIMIT);
    Window(const Window&);
    Window(Window&&) noexcept = default;
    Window& operator=(const Window& other);
    Window& operator=(Window&& other) noexcept = default;

    void push_back(const Sprite& sp);
    std::vector<std::vector<Sprite>> draws;
    std::unique_ptr<sf::RenderWindow> win;
    std::string name;
    std::size_t framerate;
};

}  // namespace sfml
}  // namespace addon
