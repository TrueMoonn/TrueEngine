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
#include "components/position.hpp"
#include "components/velocity.hpp"

#include "components/health.hpp"
#include "components/drawable.hpp"
#include "components/sprite.hpp"
#include "components/hitbox.hpp"

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

void create_projectile(ECS::Registry& reg, const Position2 &pos,
    const Velocity2 &vel) {
    static int entity_id = PROJ_VAL;

    if (entity_id > PROJ_MAX_VAL)
        entity_id = PROJ_VAL;
    reg.addComponent(entity_id, Drawable());
    reg.addComponent(entity_id, Sprite(PROJ_TEXT));
    reg.addComponent(entity_id, Hitbox(0, 0, PROJ_SIZE, PROJ_SIZE));
    reg.addComponent(entity_id, Velocity2(vel));
    reg.addComponent(entity_id, Position2(pos));
    reg.addComponent(entity_id, Health(1));
    // entity_id++;
}

void shootProjectileEvent(ECS::Registry& reg) {
    auto& players = reg.getComponents<Player>();
    auto& position = reg.getComponents<Position2>();

    for (auto &&[p, pos] : ECS::Zipper(players, position)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            create_projectile(reg, {pos.value().x + 15 - (PROJ_SIZE / 2),
                pos.value().y + 15 - (PROJ_SIZE / 2) - PROJ_VEL},
                {0, -PROJ_VEL});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            create_projectile(reg, {pos.value().x + 15 - (PROJ_SIZE / 2),
                    pos.value().y + 15 - (PROJ_SIZE / 2) + PROJ_VEL},
                {0, PROJ_VEL});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            create_projectile(reg, {pos.value().x + 15 - (PROJ_SIZE / 2)
                - PROJ_VEL, pos.value().y + 15 - (PROJ_SIZE / 2)},
                {-PROJ_VEL, 0});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            create_projectile(reg, {pos.value().x + 15 - (PROJ_SIZE / 2)
                + PROJ_VEL, pos.value().y + 15 - (PROJ_SIZE / 2)},
                {PROJ_VEL, 0});
    }
}

void manageEvent(ECS::Registry& reg) {
    std::optional<std::reference_wrapper<Window>> opt_win =
        findActiveWindow(reg.getComponents<Window>());
    if (!opt_win.has_value())
        return;
    std::reference_wrapper<Window> win = opt_win.value();

    while (std::optional event = win.get().pollEvent()) {
        if (event->is<sf::Event::Closed>())
            win.get().close();
    }
    playerMovementEvent(reg);
    shootProjectileEvent(reg);
}

}  // namespace te
