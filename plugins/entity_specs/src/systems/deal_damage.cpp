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
#include "entity_spec/components/team.hpp"

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

static mat::RectF true_hitbox(const physic::Position2 &pos, const physic::Hitbox &hit)
{
    return mat::RectF(
        mat::Vector2f(pos.x + hit.position.x, pos.y + hit.position.y),
        mat::Vector2f(hit.size.x, hit.size.y)
    );
}

std::vector<ECS::Entity> entity_hit_team(ECS::Registry& reg,
    const ECS::Entity& entity) {
    std::vector<ECS::Entity> entities_hit;

    auto& positions = reg.getComponents<physic::Position2>();
    auto& hitboxs = reg.getComponents<physic::Hitbox>();
    auto& teams = reg.getComponents<Team>();
    auto& damage = reg.getComponents<Damage>();

    auto e_hit = true_hitbox(V(positions[entity]), V(hitboxs[entity]));
    auto& e_team = V(teams[entity]);

    for (auto &&[e, pos, hit, tm, _]
        : ECS::IndexedZipper(positions, hitboxs, teams, damage)) {
        if (V(tm).name == e_team.name)
            continue;
        if (square_hitbox(e_hit, true_hitbox(V(pos), V(hit)))) {
            std::cout << "yeah" << std::endl;
            entities_hit.push_back(e);
        }
    }
    return entities_hit;
}

void deal_damage(ECS::Registry& reg) {
    auto &hit = reg.getComponents<physic::Hitbox>();
    auto &pos = reg.getComponents<physic::Position2>();
    auto &health = reg.getComponents<Health>();
    auto &damage = reg.getComponents<Damage>();
    auto &team = reg.getComponents<Team>();

    for (auto &&[id, _, _, hp, tm] : ECS::IndexedZipper(hit, pos, health, team)) {
        if (!V(hp).delay.isPaused()) {
            if (V(hp).delay.checkDelay())
                V(hp).delay.toggle();
            else
                continue;
        }
        for (auto &hit : entity_hit_team(reg, id)) {
            std::cout << "Team " << V(tm).name << " and " << V(team[hit]).name << " collided !" << std::endl;
            hp.value().reduceSafely(V(damage[hit]).amount);
            V(hp).delay.toggle();
            break;
        }
    }
}

}  // namespace eSpec
}  // namespace addon
