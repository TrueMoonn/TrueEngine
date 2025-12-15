/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** hitbox.cpp
*/

#include <cmath>

#include <ECS/Zipper.hpp>

#include "physic/components/position.hpp"
#include "physic/components/velocity.hpp"
#include "physic/components/movable.hpp"
#include "physic/components/hitbox.hpp"
#include "physic/hitbox_management.hpp"

#define isBetWeen(x, a, b) (x >= a && x <= b)

namespace addon {
namespace physic {

void hitbox2_sys(ECS::Registry& reg) {
    auto& positions = reg.getComponents<Position2>();
    auto& velocities = reg.getComponents<Velocity2>();
    auto& hitboxs = reg.getComponents<Hitbox>();
    auto& movable = reg.getComponents<Movable>();

    for (auto &&[id, pos, vel, hit, mov]
        : ECS::IndexedZipper(positions, velocities, hitboxs, movable)) {
        for (ECS::Entity cmp : entity_hit(reg, id)) {
            auto e_pos = reg.getComponents<Position2>()[cmp].value();
            auto e_hit = reg.getComponents<Hitbox>()[cmp].value();

            float dx = (pos.x + hit.size.x / 2) - (e_pos.x + e_hit.size.x / 2);
            float px = (hit.size.x / 2 + e_hit.size.x / 2) - std::fabs(dx);

            float dy = (pos.y + hit.size.y / 2) - (e_pos.y + e_hit.size.y / 2);
            float py = (hit.size.y / 2 + e_hit.size.y / 2) - std::fabs(dy);

            if (px < py)
                pos.x += (dx < 0 ? -px : px);
            else if (px > py)
                pos.y += (dy < 0 ? -py : py);
        }
    }
}

}  // namespace physic
}  // namespace addon
