/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** hitbox.cpp
*/

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
        float centerX = pos.x + hit.size.x / 2;
        float centerY = pos.y + hit.size.y / 2;

        for (ECS::Entity cmp : entity_hit(reg, id)) {
            auto other_pos = reg.getComponents<Position2>()[cmp].value();
            auto other_hit = reg.getComponents<Hitbox>()[cmp].value();

            if (isBetWeen(centerY, other_pos.y,
                other_pos.y + other_hit.size.y) &&
                isBetWeen(centerY, other_pos.x,
                other_pos.x + other_hit.size.x))
                pos.x += 15;
            if (isBetWeen(centerY, other_pos.y,
                other_pos.y + other_hit.size.y)) {
                if (other_pos.x < pos.x)
                    pos.x = other_pos.x + other_hit.size.x;
                if (other_pos.x > pos.x)
                    pos.x = other_pos.x - hit.size.x;
            }
            if (isBetWeen(centerY, other_pos.x,
                other_pos.x + other_hit.size.x)) {
                if (other_pos.y < pos.y)
                    pos.y = other_pos.y + other_hit.size.y;
                if (other_pos.y > pos.y)
                    pos.y = other_pos.y - hit.size.y;
            }
        }
    }
}

}  // namespace physic
}  // namespace addon
