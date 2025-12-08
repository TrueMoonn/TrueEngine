/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** deal_damage
*/

#include <ECS/Zipper.hpp>

#include "physic/components/hitbox.hpp"
#include "physic/components/position.hpp"
#include "entity_spec/components/health.hpp"
#include "entity_spec/components/damage.hpp"

#include "physic/hitbox_management.hpp"

namespace addon {
namespace eSpec {

void deal_damage(ECS::Registry& reg) {
    auto &hb = reg.getComponents<physic::Hitbox>();
    auto &ps = reg.getComponents<physic::Position2>();
    auto &health = reg.getComponents<Health>();
    auto &damage = reg.getComponents<Damage>();

    for (auto &&[id, h, p, hp] : ECS::IndexedZipper(hb, ps, health)) {
        for (auto &hit : physic::entity_hit(reg, id)) {
            if (!damage[hit])
                continue;
            hp.value().reduceSafely(damage[hit].value().amount);
            if (hp.value().amount == 0) {
                reg.killEntity(id);
                break;
            }
        }
    }
}

}  // namespace eSpec
}  // namespace addon
