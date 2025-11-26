/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** draw.cpp
*/

#include <ECS/Zipper.hpp>

#include "movement/components/position.hpp"
#include "window/components/drawable.hpp"
#include "window/components/sprite.hpp"
#include "components/window.hpp"

#include "window/systems/draw.hpp"

namespace te {

void draw_sys(ECS::Registry& reg) {
    auto& sprites = reg.getComponents<Sprite>();
    auto& drawables = reg.getComponents<Drawable>();
    auto& positions = reg.getComponents<Position2>();
    auto& windows = reg.getComponents<Window>();

    for (auto &&[win] : ECS::Zipper(windows)) {
        for (auto &&[sprite, pos, drawable] : ECS::Zipper(sprites, positions, drawables)) {
            sprite.value().setPosition(pos.value());
            // std::cout << pos.value().x << " " << pos.value().y << std::endl;
            // std::cout << sprite.value().getTexture().getNativeHandle() << std::endl;
            win.value().draw(sprite.value());
        }
    }
}

}  // namespace te
