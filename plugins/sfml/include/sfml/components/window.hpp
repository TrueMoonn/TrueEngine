/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** window.hpp
*/

#pragma once

    #include <string>
    #include <SFML/Graphics/RenderWindow.hpp>

namespace addon {
namespace sfml {

#define DEFAULT_FRAME_LIMIT 60
#define DEFAULT_WIN_NAME "Deepest Dungeon"
#define DEFAULT_VIDEO_MODE sf::VideoMode({1280, 720})

struct Window : public sf::RenderWindow {
    Window();
    Window(const Window&);
    Window(Window&&);

    std::string name;
};

}  // namespace sfml
}  // namespace addon
