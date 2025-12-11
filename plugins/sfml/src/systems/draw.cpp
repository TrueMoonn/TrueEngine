/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** draw.cpp
*/

#include <ECS/Zipper.hpp>

#include "physic/components/position.hpp"
#include "sfml/components/window.hpp"
#include "sfml/components/drawable.hpp"
#include "sfml/components/sprite.hpp"

#include "sfml/systems/draw.hpp"

namespace addon {
namespace sfml {

void draw_sys(ECS::Registry& reg) {
    auto& sprites = reg.getComponents<Sprite>();
    auto& drawables = reg.getComponents<Drawable>();
    auto& positions = reg.getComponents<physic::Position2>();
    auto& windows = reg.getComponents<Window>();

    for (auto &&[win] : ECS::Zipper(windows)) {
        for (auto &&[sprite, pos, drawable] :
            ECS::Zipper(sprites, positions, drawables)) {
            sprite.setPosition({pos.x, pos.y});
            win.draw(sprite);
        }
    }
}

}  // namespace sfml
}  // namespace addon
