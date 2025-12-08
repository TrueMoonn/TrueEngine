/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** hitbox.cpp
*/

#include <ECS/Zipper.hpp>

#include "movement/components/position.hpp"
#include "movement/components/velocity.hpp"

#include "physic/components/movable.hpp"
#include "physic/components/hitbox.hpp"
#include "physic/hitbox_management.hpp"

#define isBetWeen(x, a, b) (x >= a && x <= b)

namespace te {

void hitbox2_sys(ECS::Registry& reg) {
    auto& positions = reg.getComponents<Position2>();
    auto& velocities = reg.getComponents<Velocity2>();
    auto& hitboxs = reg.getComponents<Hitbox>();
    auto& movable = reg.getComponents<Movable>();

    for (auto &&[id, pos, vel, hit, mov]
        : ECS::IndexedZipper(positions, velocities, hitboxs, movable)) {
        float centerX = V(pos).x + V(hit).size.x / 2;
        float centerY = V(pos).y + V(hit).size.y / 2;

        for (ECS::Entity cmp : entity_hit(reg, id)) {
            auto other_pos = reg.getComponents<Position2>()[cmp];
            auto other_hit = reg.getComponents<Hitbox>()[cmp];

            if (isBetWeen(centerY, V(other_pos).y,
                V(other_pos).y + V(other_hit).size.y) &&
                isBetWeen(centerY, V(other_pos).x,
                V(other_pos).x + V(other_hit).size.x))
                V(pos).x += 15;
            if (isBetWeen(centerY, V(other_pos).y,
                V(other_pos).y + V(other_hit).size.y)) {
                if (V(other_pos).x < V(pos).x)
                    V(pos).x = V(other_pos).x + V(other_hit).size.x;
                if (V(other_pos).x > V(pos).x)
                    V(pos).x = V(other_pos).x - V(hit).size.x;
            }
            if (isBetWeen(centerY, V(other_pos).x,
                V(other_pos).x + V(other_hit).size.x)) {
                if (V(other_pos).y < V(pos).y)
                    V(pos).y = V(other_pos).y + V(other_hit).size.y;
                if (V(other_pos).y > V(pos).y)
                    V(pos).y = V(other_pos).y - V(hit).size.y;
            }
        }
    }
}

}  // namespace te
