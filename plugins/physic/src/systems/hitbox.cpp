/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** movement.cpp
*/

#include "movement/components/position.hpp"
#include "movement/components/velocity.hpp"

#include "physic/components/movable.hpp"
#include "physic/components/hitbox.hpp"
#include "physic/hitbox_management.hpp"

namespace te {

void hitbox2_sys(ECS::Registry& reg) {
    auto& positions = reg.getComponents<Position2>();
    auto& velocities = reg.getComponents<Velocity2>();
    auto& hitboxs = reg.getComponents<Hitbox>();
    auto& movable = reg.getComponents<Movable>();

    for (ECS::Entity entity = 0; entity < hitboxs.size() &&
        entity < velocities.size(); ++entity) {
        if (!movable[entity].has_value())
            continue;
        if (positions[entity].has_value() && velocities[entity].has_value()
            && hitboxs[entity].has_value()) {
            auto& pos = positions[entity].value();
            auto& vel = velocities[entity].value();
            // Refacto
            if (entity_hit(reg, entity).size() != 0) {
                pos.x -= vel.x;
                if (entity_hit(reg, entity).size() != 0) {
                    pos.x += vel.x;
                    pos.y -= vel.y;
                    if (entity_hit(reg, entity).size() != 0) {
                        pos.x -= vel.x;
                        return;
                    }
                }
            }
            //
        }
    }
}

}  // namespace te
