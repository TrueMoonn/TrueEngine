/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** hitbox.cpp
*/

#include <ECS/Zipper.hpp>

#include "entity_spec/components/team.hpp"
#include "entity_spec/components/damage.hpp"

#include "entity_spec/hitbox.hpp"

namespace addon {
namespace eSpec {

bool square_hitbox(mat::RectF rect1, mat::RectF rect2) {
    return (rect1.position.x < rect2.position.x + rect2.size.x &&
        rect1.position.x + rect1.size.x > rect2.position.x &&
        rect1.position.y < rect2.position.y + rect2.size.y &&
        rect1.position.y + rect1.size.y > rect2.position.y);
}

mat::RectF true_hitbox(const physic::Position2 &pos,
    const physic::Hitbox &hit) {
    return mat::RectF(
        mat::Vector2f(pos.x + hit.position.x, pos.y + hit.position.y),
        mat::Vector2f(hit.size.x, hit.size.y));
}

std::vector<ECS::Entity> entity_hit_team(ECS::Registry& reg,
    const ECS::Entity& entity) {
    std::vector<ECS::Entity> entities_hit;

    auto& positions = reg.getComponents<physic::Position2>();
    auto& hitboxs = reg.getComponents<physic::Hitbox>();
    auto& teams = reg.getComponents<Team>();
    auto& damage = reg.getComponents<Damage>();

    auto e_hit = true_hitbox(positions[entity].value(),
        hitboxs[entity].value());
    auto& e_team = teams[entity].value();

    for (auto &&[e, pos, hit, tm, _]
        : ECS::IndexedZipper(positions, hitboxs, teams, damage)) {
        if (tm.name == e_team.name)
            continue;
        if (square_hitbox(e_hit, true_hitbox(pos, hit))) {
            entities_hit.push_back(e);
        }
    }
    return entities_hit;
}

}  // namespace eSpec
}  // namespace addon
