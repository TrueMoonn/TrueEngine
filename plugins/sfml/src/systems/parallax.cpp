/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** parallax.cpp
*/

#include <ECS/Registry.hpp>
#include <ECS/Zipper.hpp>

#include "display/components/parallax.hpp"
#include "physic/components/position.hpp"
#include "sfml/components/sprite.hpp"
#include "sfml/components/drawable.hpp"

#include "sfml/components/window.hpp"
#include "sfml/systems/parallax.hpp"

namespace addon {
namespace sfml {

void parallax_sys(ECS::Registry &reg) {
    auto& windows = reg.getComponents<Window>();
    auto& parallaxs = reg.getComponents<display::Parallax>();
    auto& sprites = reg.getComponents<Sprite>();
    auto& drawables = reg.getComponents<Drawable>();
    auto& positions = reg.getComponents<physic::Position2>();

    for (auto&& [win] : ECS::Zipper(windows)) {
        for (auto&& [para, sp, draw, pos] :
            ECS::Zipper(parallaxs, sprites, drawables, positions)) {
            auto size = sp.sp.getTextureRect().size;
            size.x *= sp.sp.getScale().x;
            size.y *= sp.sp.getScale().y;
            if (para.reset.x > pos.x + size.x ||
                para.reset.y > pos.y + size.y) {
                pos.x = para.reset.x;
                pos.y = para.reset.y;
            }
            for (std::size_t i = 0; i < para.iterations; ++i) {
                sp.sp.setPosition({pos.x + size.x * i, pos.y + size.y * i});
                win.push_back(sp);
            }
        }
    }
}

}  // namespace sfml
}  // namespace addon
