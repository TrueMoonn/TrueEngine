/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** deal_damage
*/

#include <ECS/Zipper.hpp>

#include "entity_spec/components/health.hpp"

#include "physic/hitbox_management.hpp"

namespace addon {
namespace eSpec {

void kill_entity(ECS::Registry& reg) {
    auto &health = reg.getComponents<Health>();

    for (auto &&[id, hp] : ECS::IndexedZipper(health))
        if (hp.value().amount == 0)
            reg.killEntity(id);
}

}  // namespace eSpec
}  // namespace addon
