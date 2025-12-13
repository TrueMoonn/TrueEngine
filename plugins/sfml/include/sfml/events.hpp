/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** events.hpp
*/

#pragma once

    #include <vector>
    #include <optional>

    #include <event/EventManager.hpp>

namespace addon {
namespace sfml {

void getKeyboardEvent(std::optional<sf::Event>, te::event::KeysEvent&);
void getMouseEvent(std::optional<sf::Event>, te::event::MouseEvent&);
void pollEvent(te::event::Events& events, ECS::Registry& reg);

}  // namespace sfml
}  // namespace addon
