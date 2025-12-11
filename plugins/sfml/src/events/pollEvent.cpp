/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** pollEvent.cpp
*/

#include <ECS/Zipper.hpp>
#include "sfml/components/window.hpp"

#include "sfml/events.hpp"

namespace addon {
namespace sfml {

void pollEvent(te::event::Events& events, ECS::Registry& reg) {
    auto& windows = reg.getComponents<Window>();

    for (auto&& [win] : ECS::Zipper(windows)) {
        while (std::optional<sf::Event> pevent = win.value().pollEvent()) {
            getKeyboardEvent(pevent, events.keys);
            getMouseEvent(pevent, events.keys);
            if (pevent->is<sf::Event::Closed>())
                events.systems.at(te::event::System::Closed) = true;
        }
    }
}

}  // namespace sfml
}  // namespace addon
