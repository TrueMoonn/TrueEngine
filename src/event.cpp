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
#include "window.hpp"
#include "interaction/components/player.hpp"
#include "movement/components/position.hpp"
#include "movement/components/velocity.hpp"
#include "display/components/sprite.hpp"
#include "window.hpp"
#include "interaction/components/player.hpp"
#include "movement/components/position.hpp"
#include "movement/components/velocity.hpp"

#include "event.hpp"

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

// void create_projectile(ECS::Registry& reg, const Position2 &pos,
//     const Velocity2 &vel) {
//     static int entity_id = PROJ_VAL;

//     if (entity_id > PROJ_MAX_VAL)
//         entity_id = PROJ_VAL;
//     reg.addComponent(entity_id, Drawable());
//     reg.addComponent(entity_id, Sprite(sf::Texture(sf::Image(sf::Vector2u(PROJ_SIZE, PROJ_SIZE),
//         sf::Color::Green)), sf::Vector2f(2, 2)));
//     reg.addComponent(entity_id, Hitbox(0, 0, PROJ_SIZE, PROJ_SIZE));
//     reg.addComponent(entity_id, Velocity2(vel));
//     reg.addComponent(entity_id, Position2(pos));
//     reg.addComponent(entity_id, Health(1));
//     // entity_id++;
// }

// void shootProjectileEvent(ECS::Registry& reg) {
//     auto& players = reg.getComponents<Player>();
//     auto& position = reg.getComponents<Position2>();
//     auto& event = reg.getComponents<Event>()[0];

//     for (auto &&[p, pos] : ECS::Zipper(players, position)) {
//         if (event.value()._Keys[te::Up])
//             create_projectile(reg, {pos.value().x + 15 - (PROJ_SIZE / 2),
//                 pos.value().y + 15 - (PROJ_SIZE / 2) - PROJ_VEL},
//                 {0, -PROJ_VEL});
//         if (event.value()._Keys[te::Down])
//             create_projectile(reg, {pos.value().x + 15 - (PROJ_SIZE / 2),
//                     pos.value().y + 15 - (PROJ_SIZE / 2) + PROJ_VEL},
//                 {0, PROJ_VEL});
//         if (event.value()._Keys[te::Left])
//             create_projectile(reg, {pos.value().x + 15 - (PROJ_SIZE / 2)
//                 - PROJ_VEL, pos.value().y + 15 - (PROJ_SIZE / 2)},
//                 {-PROJ_VEL, 0});
//         if (event.value()._Keys[te::Right])
//             create_projectile(reg, {pos.value().x + 15 - (PROJ_SIZE / 2)
//                 + PROJ_VEL, pos.value().y + 15 - (PROJ_SIZE / 2)},
//                 {PROJ_VEL, 0});
//     }
// }

void manageWindow(ECS::Registry& reg, std::reference_wrapper<Window> win) {
    auto& event = reg.getComponents<Event>()[0];

    if (event.value()._Keys[te::Escape]) {
        win.get().close();
    }
    if (event.value()._Keys[te::LostFocus]) {

    }
}

void handleEvent(const sf::Event& event, auto &Event, std::reference_wrapper<Window> win) {
    if (const auto* e = event.getIf<sf::Event::Closed>()) {
        win.get().close();
    }
    else if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
        Event.value()._Keys[(te::Key)e->code] = true;
        std::cout << (te::Key)e->code << std::endl;
    }
    else if (const auto* e = event.getIf<sf::Event::KeyReleased>()) {
        Event.value()._Keys[(te::Key)e->code] = false;
    }
    else if (const auto* e = event.getIf<sf::Event::Resized>()) {
        sf::View view = win.get().getDefaultView();

        view.setSize({
            static_cast<float>(e->size.x),
            static_cast<float>(e->size.y)
        });
        win.get().setView(view);
    }
    else if (const auto* e = event.getIf<sf::Event::MouseButtonPressed>()) {
        Event.value()._Systems[te::System::MouseButtonPressed] = true;
    
        if (auto it = te::_Mouse.find(e->button); it != te::_Mouse.end()) {
            size_t idx = it->second;
            Event.value()._MouseButtons[idx].first = true;
            Event.value()._MouseButtons[idx].second.x = e->position.x;
            Event.value()._MouseButtons[idx].second.y = e->position.y;
        }
    }
    else if (const auto* e = event.getIf<sf::Event::MouseMoved>()) {
        Event.value()._Systems[te::System::MouseMoved] = true;
    }
    else if (const auto* e = event.getIf<sf::Event::MouseEntered>()) {
        Event.value()._Systems[te::System::MouseEntered] = true;
    }
    else if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
        Event.value()._Systems[te::System::MouseButtonReleased] = true;
    }
    else if (const auto *e = event.getIf<sf::Event::FocusLost>()) {
        Event.value()._Systems[te::System::LostFocus] = true;
    }
    else if (const auto *e = event.getIf<sf::Event::FocusGained>()) {
        Event.value()._Systems[te::System::GainedFocus] = true;
    }
}

void manageEvent(ECS::Registry& reg) {
    auto &Event = reg.getComponents<te::Event>()[0];

    std::optional<std::reference_wrapper<Window>> opt_win =
        findActiveWindow(reg.getComponents<Window>());
    if (!opt_win.has_value() || !Event.has_value() )
        return;
    std::reference_wrapper<Window> win = opt_win.value();

    while (std::optional<sf::Event> event = win.get().pollEvent()) {
        handleEvent(*event, Event, win);
    }
    playerMovementEvent(reg);
    // shootProjectileEvent(reg);
    manageWindow(reg, win);
}

}  // namespace te
