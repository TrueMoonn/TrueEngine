/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** deal_damage
*/

#include <ECS/Zipper.hpp>

#include "entity_spec/components/health.hpp"
#include "entity_spec/components/fragile.hpp"
#include "entity_spec/components/timeout.hpp"

#include "physic/hitbox_management.hpp"

namespace addon {
namespace eSpec {

void kill_entity(ECS::Registry& reg) {
    for (auto &&[id, hp] : ECS::IndexedZipper(reg.getComponents<Health>()))
        if (hp.amount == 0)
            reg.killEntity(id);
    for (auto &&[id, fr] : ECS::IndexedZipper(reg.getComponents<Fragile>()))
        if (fr.destroyed)
            reg.killEntity(id);
    for (auto &&[id, to] : ECS::IndexedZipper(reg.getComponents<Timeout>()))
        if (to.delta.checkDelay(false))
            reg.killEntity(id);
}

}  // namespace eSpec
}  // namespace addon
