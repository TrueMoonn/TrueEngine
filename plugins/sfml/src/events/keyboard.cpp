/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** keyboard.cpp
*/

#include "sfml/events/endpoint.hpp"

void getKeyboardEvent(std::optional<sf::Event> pevent, te::KeysEvent& keys) {
    if (pevent->is<sf::Event::KeyPressed>())
        keys[te::Key(pevent->getIf<sf::Event::KeyPressed>()->code)] = true;
    if (pevent->is<sf::Event::KeyReleased>())
        keys[te::Key(pevent->getIf<sf::Event::KeyReleased>()->code)] = false;
}
