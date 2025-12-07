/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** endpoint.hpp
*/

#pragma once

    #include <vector>

    #include <ECS/Zipper.hpp>
    #include <EventManager.hpp>

    #include "sfml/components/window.hpp"

void getKeyboardEvent(std::optional<sf::Event>, te::KeysEvent&);

extern "C" {
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
}
