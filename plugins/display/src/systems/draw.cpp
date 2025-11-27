/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** draw.cpp
*/

#include <ECS/Zipper.hpp>

#include "window.hpp"
#include "movement/components/position.hpp"
#include "display/components/drawable.hpp"
#include "display/components/sprite.hpp"

#include "display/systems/draw.hpp"

namespace te {

void draw_sys(ECS::Registry& reg) {
    auto& sprites = reg.getComponents<Sprite>();
    auto& drawables = reg.getComponents<Drawable>();
    auto& positions = reg.getComponents<Position2>();
    auto& windows = reg.getComponents<Window>();

    for (auto &&[win] : ECS::Zipper(windows)) {
        for (auto &&[sprite, pos, drawable] :
            ECS::Zipper(sprites, positions, drawables)) {
            sprite.value().setPosition(pos.value());
            win.value().draw(sprite.value());
        }
    }
}

}  // namespace te
