/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** hitbox_management.cpp
*/

#include <vector>

#include <ECS/Registry.hpp>
#include <ECS/DenseZipper.hpp>

#include "ECS/DenseSA.hpp"
#include "maths/Rect.hpp"

#include "physic/components/position.hpp"
#include "physic/components/velocity.hpp"
#include "physic/components/hitbox.hpp"
#include "physic/components/movable.hpp"
#include "physic/hitbox_management.hpp"

namespace addon {
namespace physic {

static bool square_hitbox(mat::RectF rect1, mat::RectF rect2) {
    return (rect1.position.x < rect2.position.x + rect2.size.x &&
        rect1.position.x + rect1.size.x > rect2.position.x &&
        rect1.position.y < rect2.position.y + rect2.size.y &&
        rect1.position.y + rect1.size.y > rect2.position.y);
}

std::vector<ECS::Entity> entity_hit(ECS::Registry& reg,
    const ECS::Entity& entity) {
    std::vector<ECS::Entity> entities_hit;

    auto& positions = reg.getComponents<Position2>();
    auto& hitboxs = reg.getComponents<Hitbox>();
    auto& stationary = reg.getComponents<Stationary>();

    auto& pos = GET_ENTITY_CMPT(positions, entity);
    auto hitbox = GET_ENTITY_CMPT(hitboxs, entity);

    for (auto &&[e, obj_pos, obj_hitbox, _] :
        ECS::IndexedDenseZipper(positions, hitboxs, stationary)) {
        if (e != entity) {
            if (square_hitbox(
                mat::RectF(
                    mat::Vector2f
                    (pos.x + hitbox.position.x, pos.y + hitbox.position.y),
                    mat::Vector2f(
                    hitbox.size.x, hitbox.size.y)),
                mat::RectF(
                    mat::Vector2f(
                    obj_pos.x + obj_hitbox.position.x,
                    obj_pos.y + obj_hitbox.position.y),
                    mat::Vector2f(
                    obj_hitbox.size.x,
                    obj_hitbox.size.y)))) {
                entities_hit.push_back(e);
            }
        }
    }
    return entities_hit;
}

}  // namespace physic
}  // namespace addon
