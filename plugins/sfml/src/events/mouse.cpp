/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** keyboard.cpp
*/

#include <unordered_map>

#include <SFML/Window/Event.hpp>

#include "sfml/events.hpp"

namespace addon {
namespace sfml {

static const std::unordered_map<sf::Mouse::Button, te::event::MouseButton>
    _Mouse = {{
    {sf::Mouse::Button::Left, te::event::MouseButton::MouseLeft},
    {sf::Mouse::Button::Right, te::event::MouseButton::MouseRight},
    {sf::Mouse::Button::Middle, te::event::MouseButton::MouseMiddle},
}};

void getMouseEvent(std::optional<sf::Event> pevent,
    te::event::MouseEvent& mouse) {
    if (pevent->is<sf::Event::MouseButtonPressed>()) {
        mouse.update = true;
        const auto* e = pevent->getIf<sf::Event::MouseButtonPressed>();
        if (auto it = _Mouse.find(e->button); it != _Mouse.end()) {
            size_t idx = it->second;
            mouse._MouseKey[idx].active = true;
            mouse._MouseKey[idx].x = e->position.x;
            mouse._MouseKey[idx].y = e->position.y;
        }
    } else if (pevent->is<sf::Event::MouseButtonReleased>()) {
        mouse.update = true;
        const auto* e = pevent->getIf<sf::Event::MouseButtonReleased>();
        if (auto it = _Mouse.find(e->button); it != _Mouse.end()) {
            size_t idx = it->second;
            mouse._MouseKey[idx].active = false;
            mouse._MouseKey[idx].x = e->position.x;
            mouse._MouseKey[idx].y = e->position.y;
        }
    }
}

}  // namespace sfml
}  // namespace addon
