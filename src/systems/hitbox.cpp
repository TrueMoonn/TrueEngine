/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** movement.cpp
*/

#include "components/position.hpp"
#include "components/velocity.hpp"
#include "components/movable.hpp"
#include "components/hitbox.hpp"
#include "hitbox_management.hpp"

#include "systems/movement.hpp"

#include <ECS/Zipper.hpp>

#define V(a) a.value()

#define isBetWeen(x, a, b) (x >= a && x <= b)

namespace te {

void hitbox2_sys(ECS::Registry& reg) {
    auto& positions = reg.getComponents<Position2>();
    auto& velocities = reg.getComponents<Velocity2>();
    auto& hitboxs = reg.getComponents<Hitbox>();
    auto& movable = reg.getComponents<Movable>();

    for (auto &&[id, pos, vel, hit, mov]
        : ECS::IndexedZipper(positions, velocities, hitboxs, movable)) {
        Position2 center(V(pos).x + V(hit).size.x / 2, V(pos).y + V(hit).size.y / 2);

        for (ECS::Entity cmp : entity_hit(reg, id)) {
            auto other_pos = reg.getComponents<Position2>()[cmp];
            auto other_hit = reg.getComponents<Hitbox>()[cmp];

            if (isBetWeen(center.y, V(other_pos).y, V(other_pos).y + V(other_hit).size.y)) {
                if (V(other_pos).x < V(pos).x)
                    V(pos).x = V(other_pos).x + V(other_hit).size.x;
                if (V(other_pos).x > V(pos).x)
                    V(pos).x = V(other_pos).x - V(hit).size.x;
            }
            if (isBetWeen(center.x, V(other_pos).x, V(other_pos).x + V(other_hit).size.x)) {
                if (V(other_pos).y < V(pos).y)
                    V(pos).y = V(other_pos).y + V(other_hit).size.y;
                if (V(other_pos).y > V(pos).y)
                    V(pos).y = V(other_pos).y - V(hit).size.y;
            }
        }
    }
}

}  // namespace te
