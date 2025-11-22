/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** movement.cpp
*/

#include <ECS/Zipper.hpp>

#include "components/position.hpp"
#include "components/velocity.hpp"
#include "components/movable.hpp"
#include "components/hitbox.hpp"
#include "hitbox_management.hpp"

#include "systems/movement.hpp"

namespace te {

void hitbox2_sys(ECS::Registry& reg) {
    auto& positions = reg.getComponents<Position2>();
    auto& velocities = reg.getComponents<Velocity2>();
    auto& hitboxs = reg.getComponents<Hitbox>();
    auto& movable = reg.getComponents<Movable>();

    for (auto &&[id, pos, vel, hit, mob] : ECS::IndexedZipper(positions,
        velocities, hitboxs, movable)) {
        if (entity_hit(reg, id).size() != 0) {
            pos.value().x -= vel.value().x;
            if (entity_hit(reg, id).size() != 0) {
                pos.value().x += vel.value().x;
                pos.value().y -= vel.value().y;
                if (entity_hit(reg, id).size() != 0) {
                    pos.value().x -= vel.value().x;
                    return;
                }
            }
        }
    }
}

}  // namespace te
