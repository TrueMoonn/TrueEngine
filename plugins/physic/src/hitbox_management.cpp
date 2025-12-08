/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** hitbox_management.cpp
*/

#include <vector>

#include <ECS/Registry.hpp>
#include <ECS/Zipper.hpp>

#include "maths/Rect.hpp"

#include "physic/components/position.hpp"
#include "physic/components/velocity.hpp"
#include "physic/components/hitbox.hpp"
#include "physic/hitbox_management.hpp"

static bool square_hitbox(te::mat::RectF rect1, te::mat::RectF rect2) {
    return (rect1.position.x < rect2.position.x + rect2.size.x &&
        rect1.position.x + rect1.size.x > rect2.position.x &&
        rect1.position.y < rect2.position.y + rect2.size.y &&
        rect1.position.y + rect1.size.y > rect2.position.y);
}

std::vector<ECS::Entity> entity_hit(ECS::Registry& reg,
    const ECS::Entity& entity) {
    std::vector<ECS::Entity> entities_hit;

    auto& positions = reg.getComponents<te::Position2>();
    auto& hitboxs = reg.getComponents<te::Hitbox>();

    auto& pos = positions[entity].value();
    auto hitbox = hitboxs[entity].value();

    for (auto &&[e, obj_pos, obj_hitbox] :
        ECS::IndexedZipper(positions, hitboxs)) {
        if (e != entity) {
            if (square_hitbox(
                te::mat::RectF(
                    te::mat::Vector2f
                    (pos.x + hitbox.position.x, pos.y + hitbox.position.y),
                    te::mat::Vector2f(
                    hitbox.size.x, hitbox.size.y)),
                te::mat::RectF(
                    te::mat::Vector2f(
                    obj_pos.value().x + obj_hitbox.value().position.x,
                    obj_pos.value().y + obj_hitbox.value().position.y),
                    te::mat::Vector2f(
                    obj_hitbox.value().size.x,
                    obj_hitbox.value().size.y)))) {
                entities_hit.push_back(e);
            }
        }
    }
    return entities_hit;
}
