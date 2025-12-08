/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** events.hpp
*/

#pragma once

    #include <vector>
    #include <optional>

    #include <EventManager.hpp>

namespace addon {
namespace sfml {

void getKeyboardEvent(std::optional<sf::Event>, te::KeysEvent&);
void pollEvent(te::Events& events, ECS::Registry& reg);

}  // namespace sfml
}  // namespace addon
