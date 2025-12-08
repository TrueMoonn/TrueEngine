/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** movement.cpp
*/

#include "physic/components/position.hpp"
#include "physic/components/velocity.hpp"

#include "physic/systems/movement.hpp"

namespace addon {
namespace physic {


void movement2_sys(ECS::Registry& reg) {
    auto& positions = reg.getComponents<Position2>();
    auto& velocities = reg.getComponents<Velocity2>();

    for (ECS::Entity entity = 0; entity < positions.size() &&
        entity < velocities.size(); ++entity) {
        if (positions[entity].has_value() && velocities[entity].has_value()) {
            auto& pos = positions[entity].value();
            auto& vel = velocities[entity].value();
            pos += vel;
        }
    }
}

}  // namespace physic
}  // namespace addon
