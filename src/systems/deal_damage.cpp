/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** deal_damage
*/

#include <ECS/Zipper.hpp>

#include "components/hitbox.hpp"
#include "components/position.hpp"
#include "components/health.hpp"
#include "components/damage.hpp"

#include "hitbox_management.hpp"

namespace te {

void deal_damage(ECS::Registry& reg) {
    auto &hb = reg.getComponents<Hitbox>();
    auto &ps = reg.getComponents<Position2>();
    auto &health = reg.getComponents<Health>();
    auto &damage = reg.getComponents<Damage>();

    for (auto &&[id, h, p, hp] : ECS::IndexedZipper(hb, ps, health)) {
        for (auto &hit : entity_hit(reg, id)) {
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

}  // namespace te
