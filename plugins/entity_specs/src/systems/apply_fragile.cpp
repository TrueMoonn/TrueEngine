/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** deal_damage
*/

#include <ECS/Zipper.hpp>

#include "physic/components/hitbox.hpp"
#include "physic/components/position.hpp"

#include "entity_spec/components/fragile.hpp"

#include "maths/Rect.hpp"

#include "physic/hitbox_management.hpp"

namespace addon {
namespace eSpec {

static bool square_hitbox(mat::RectF rect1, mat::RectF rect2) {
    return (rect1.position.x < rect2.position.x + rect2.size.x &&
        rect1.position.x + rect1.size.x > rect2.position.x &&
        rect1.position.y < rect2.position.y + rect2.size.y &&
        rect1.position.y + rect1.size.y > rect2.position.y);
}

static mat::RectF true_hitbox(const physic::Position2 &pos
        , const physic::Hitbox &hit) {
    return mat::RectF(
        mat::Vector2f(pos.x + hit.position.x, pos.y + hit.position.y),
        mat::Vector2f(hit.size.x, hit.size.y));
}

void apply_fragile(ECS::Registry& reg) {
    auto &hitbox = reg.getComponents<physic::Hitbox>();
    auto &position = reg.getComponents<physic::Position2>();
    auto &fragile = reg.getComponents<Fragile>();
    auto &robust = reg.getComponents<Robust>();

    for (auto &&[e_id, e_pos, e_hit, e_frag]
            : ECS::IndexedZipper(position, hitbox, fragile)) {
        auto e_truehit = true_hitbox(e_pos, e_hit);
        for (auto &&[id, pos, hit, rob]
                : ECS::IndexedZipper(position, hitbox, robust)) {
            if (e_id == id || e_frag.priority >= rob.priority ||
                !square_hitbox(e_truehit, true_hitbox(pos, hit)))
                continue;
            e_frag.destroyed = true;
            break;
        }
    }
}

}  // namespace eSpec
}  // namespace addon
