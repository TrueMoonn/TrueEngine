/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** movement.cpp
*/

#include "components/position.hpp"
#include "components/velocity.hpp"
#include "components/hitbox.hpp"
#include "hitbox_management.hpp"

#include "systems/movement.hpp"

void movement2_sys(ECS::Registry& reg)
{
    auto& positions = reg.getComponents<Position2>();
    auto& velocities = reg.getComponents<Velocity2>();

    for (ECS::Entity entity = 0; entity < positions.size() && entity < velocities.size(); ++entity) {
        if (positions[entity].has_value() && velocities[entity].has_value()) {
            auto& pos = positions[entity].value();
            auto& vel = velocities[entity].value();
            pos += vel;
        }
    }
}

void movement3_sys(ECS::Registry& reg)
{
    auto& positions = reg.getComponents<Position3>();
    auto& velocities = reg.getComponents<Velocity3>();

    for (size_t entity = 0; entity < positions.size() && entity < velocities.size(); ++entity) {
        if (positions[entity].has_value() && velocities[entity].has_value()) {
            auto& pos = positions[entity].value();
            auto& vel = velocities[entity].value();
            pos += vel;
        }
    }
}
