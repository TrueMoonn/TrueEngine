/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** interaction.cpp
*/

#include <SFML/Window/Event.hpp>

#include "interaction/components/player.hpp"
#include "interaction/components/interactive.hpp"
#include "interaction/systems/interaction.hpp"

namespace te {

static void interaction_hitbox(ECS::Registry& reg) {
    auto& players = reg.getComponents<Player>();
    auto& interactives = reg.getComponents<Interactive>();

    for (ECS::Entity e = 0; e < players.size() &&
        e < interactives.size(); ++e) {
        if (players[e].has_value() && interactives[e].has_value()) {
            // entity_interaction(reg, e);
        }
    }
}

void player_interaction_sys(ECS::Registry& reg) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        interaction_hitbox(reg);
    }
}

}  // namespace te

