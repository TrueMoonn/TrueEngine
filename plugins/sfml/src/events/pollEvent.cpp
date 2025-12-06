/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** pollEvent.cpp
*/

#include <ECS/Zipper.hpp>
#include "sfml/components/window.hpp"

#include "sfml/events.hpp"

void pollEvent(te::Events& events, ECS::Registry& reg) {
    auto& windows = reg.getComponents<te::Window>();

    for (auto&& [win] : ECS::Zipper(windows)) {
        while (std::optional<sf::Event> pevent = win.value().pollEvent()) {
            getKeyboardEvent(pevent, events.keys);
            if (pevent->is<sf::Event::Closed>())
                events.systems.at(te::System::Closed) = true;
        }
    }
}
