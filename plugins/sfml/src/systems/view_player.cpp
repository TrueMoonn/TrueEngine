/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** view_player.cpp
*/

#include <ECS/Zipper.hpp>

#include "interaction/components/player.hpp"
#include "physic/components/position.hpp"
#include "sfml/components/window.hpp"

#include "sfml/systems/view_player.hpp"

namespace te {

void follow_player_sys(ECS::Registry& reg) {
    auto& players = reg.getComponents<Player>();
    auto& positions = reg.getComponents<Position2>();
    auto& windows = reg.getComponents<Window>();

    for (auto &&[win] : ECS::Zipper(windows)) {
        for (auto &&[pos, player] : ECS::Zipper(positions, players)) {
            win.value().setView(sf::View({V(pos).x, V(pos).y},
                static_cast<sf::Vector2f>(win.value().getSize())));
        }
    }
}

}  // namespace te
