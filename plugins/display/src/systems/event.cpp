/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** event.cpp
*/

#include <memory.h>
#include <variant>

#include <SFML/Window/Event.hpp>

#include <ECS/Zipper.hpp>

#include "display/components/window.hpp"
#include "interaction/components/player.hpp"
#include "movement/components/position.hpp"
#include "movement/components/velocity.hpp"
#include "display/components/sprite.hpp"

#include "display/systems/event.hpp"

#include "entity_spec/components/health.hpp"
#include "physic/components/hitbox.hpp"
#include "display/components/drawable.hpp"

namespace te {

void playerMovementEvent(ECS::Registry& reg) {
    auto& players = reg.getComponents<Player>();
    auto& event = reg.getComponents<Event>()[0];
    auto& velocities = reg.getComponents<Velocity2>();

     for (auto &&[id, pos, vel] : ECS::IndexedZipper(players,
        velocities)) {
        if (event.value()._Keys[te::Q])
             vel.value().x = P_MOVEMENT.at(P_LEFT_MOV);
        else if (event.value()._Keys[te::D])
            vel.value().x = P_MOVEMENT.at(P_RIGHT_MOV);
        else
            vel.value().x = 0.0f;
        if (event.value()._Keys[te::Z])
            vel.value().y = P_MOVEMENT.at(P_TOP_MOV);
        else if (event.value()._Keys[te::S])
            vel.value().y = P_MOVEMENT.at(P_BOT_MOV);
        else
            vel.value().y = 0.0f;
    }
}

void manageWindow(ECS::Registry& reg, Window& win) {
    auto& event = reg.getComponents<Event>()[0];

    if (event.value()._Keys[te::Escape]) {
        win.close();
    }
}

void handleEvent(const sf::Event& event, auto &Event,
                 std::reference_wrapper<Window> win) {
    if (const auto* e = event.getIf<sf::Event::Closed>()) {
        win.get().close();
    } else if (const auto* e =
        event.getIf<sf::Event::KeyPressed>()) {
        Event.value()._Keys[(te::Key)e->code] = true;
    } else if (const auto* e =
        event.getIf<sf::Event::KeyReleased>()) {
        Event.value()._Keys[(te::Key)e->code] = false;
    } else if (const auto* e =
        event.getIf<sf::Event::Resized>()) {
        sf::View view = win.get().getDefaultView();

        view.setSize({
            static_cast<float>(e->size.x),
            static_cast<float>(e->size.y)
        });
        win.get().setView(view);
    } else if (const auto* e =
        event.getIf<sf::Event::MouseButtonPressed>()) {
        Event.value()._Systems[te::System::MouseButtonPressed] = true;
        if (auto it = te::_Mouse.find(e->button); it != te::_Mouse.end()) {
            size_t idx = it->second;
            Event.value()._MouseButtons[idx].first = true;
            Event.value()._MouseButtons[idx].second.x = e->position.x;
            Event.value()._MouseButtons[idx].second.y = e->position.y;
        }
    } else if (const auto* e =
        event.getIf<sf::Event::MouseMoved>()) {
        Event.value()._Systems[te::System::MouseMoved] = true;
    } else if (const auto* e =
        event.getIf<sf::Event::MouseEntered>()) {
        Event.value()._Systems[te::System::MouseEntered] = true;
    } else if (const auto* e =
        event.getIf<sf::Event::MouseButtonReleased>()) {
        Event.value()._Systems[te::System::MouseButtonReleased] = true;
    } else if (const auto *e =
        event.getIf<sf::Event::FocusLost>()) {
        Event.value()._Systems[te::System::LostFocus] = true;
    } else if (const auto *e =
        event.getIf<sf::Event::FocusGained>()) {
        Event.value()._Systems[te::System::GainedFocus] = true;
    }
}

void manageEvent(ECS::Registry& reg) {
    auto &Event = reg.getComponents<te::Event>()[0];
    auto &windows = reg.getComponents<te::Window>();

    for (auto&& [win] : ECS::Zipper(windows)) {
        while (std::optional<sf::Event> event = win.value().pollEvent()) {
            handleEvent(*event, Event, win.value());
        }
        manageWindow(reg, win.value());
    }
    playerMovementEvent(reg);
}

}  // namespace te
