/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** movement.cpp
*/

#include <ECS/Zipper.hpp>
#include "clock.hpp"
#include "physic/components/position.hpp"
#include "physic/components/velocity.hpp"

#include "physic/systems/movement.hpp"

namespace addon {
namespace physic {

void movement2_sys(ECS::Registry& reg) {
    static te::Timestamp delta(0.f);
    auto& positions = reg.getComponents<Position2>();
    auto& velocities = reg.getComponents<Velocity2>();

    float elapsed = delta.getElapsedTime();
    for (auto&&[pos, vel] : ECS::Zipper(positions, velocities)) {
        pos.x += vel.x * elapsed / 1000000;
        pos.y += vel.y * elapsed / 1000000;
    }
    delta.restart();
}

}  // namespace physic
}  // namespace addon
