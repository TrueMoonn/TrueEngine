/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** keyboard.cpp
*/

#include <SFML/Window/Event.hpp>

#include "sfml/events.hpp"

namespace addon {
namespace sfml {

void getKeyboardEvent(std::optional<sf::Event> pevent, te::KeysEvent& keys) {
    if (pevent->is<sf::Event::KeyPressed>()) {
        keys.keys[te::Key(pevent->getIf<sf::Event::KeyPressed>()->code)] = true;
        keys.update = true;
    } else if (pevent->is<sf::Event::KeyReleased>()) {
        keys.keys[te::Key(
            pevent->getIf<sf::Event::KeyReleased>()->code)] = false;
        keys.update = true;
    }
}

}  // namespace sfml
}  // namespace addon
