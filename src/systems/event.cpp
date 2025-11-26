/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** event.cpp
*/

#include <SFML/Window/Event.hpp>

#include <ECS/Zipper.hpp>

#include "systems/event.hpp"
#include "components/window.hpp"
#include "components/player.hpp"
#include "movement/components/position.hpp"
#include "movement/components/velocity.hpp"

namespace te {

void playerMovementEvent(ECS::Registry& reg) {
    auto& players = reg.getComponents<Player>();

    for (ECS::Entity e = 0; e < players.size(); ++e) {
        if (players[e].has_value()) {
            auto& velocities = reg.getComponents<Velocity2>();
            if (e < velocities.size() && velocities[e].has_value()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                    velocities[e].value().x = P_MOVEMENT.at(P_LEFT_MOV);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                    velocities[e].value().x = P_MOVEMENT.at(P_RIGHT_MOV);
                else
                    velocities[e].value().x = 0.0f;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
                    velocities[e].value().y = P_MOVEMENT.at(P_TOP_MOV);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                    velocities[e].value().y = P_MOVEMENT.at(P_BOT_MOV);
                else
                    velocities[e].value().y = 0.0f;
            }
        }
    }
}

void manageEvent(ECS::Registry& reg) {
    auto& windows = reg.getComponents<te::Window>();

    for (auto &&[win] : ECS::Zipper(windows)) {
        while (std::optional event = win.value().pollEvent()) {
            if (event->is<sf::Event::Closed>())
                win.value().close();
        }
        playerMovementEvent(reg);
    }
}

}  // namespace te
