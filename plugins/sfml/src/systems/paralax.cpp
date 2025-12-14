/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** paralax.cpp
*/

#include <ECS/Registry.hpp>
#include <ECS/Zipper.hpp>

#include "display/components/paralax.hpp"
#include "physic/components/position.hpp"
#include "sfml/components/sprite.hpp"
#include "sfml/components/drawable.hpp"

#include "sfml/components/window.hpp"
#include "sfml/systems/paralax.hpp"

namespace addon {
namespace sfml {

void paralax_sys(ECS::Registry &reg) {
    auto& windows = reg.getComponents<Window>();
    auto& paralaxs = reg.getComponents<display::Paralax>();
    auto& sprites = reg.getComponents<Sprite>();
    auto& drawables = reg.getComponents<Drawable>();
    auto& positions = reg.getComponents<physic::Position2>();

    for (auto&& [win] : ECS::Zipper(windows)) {
        for (auto&& [para, sp, draw, pos] :
            ECS::Zipper(paralaxs, sprites, drawables, positions)) {
            auto size = sp.sp.getTextureRect().size;
            size.x *= sp.sp.getScale().x;
            size.y *= sp.sp.getScale().y;
            if (para.reset.x > pos.x + size.x) {
                pos.x = para.reset.x;
            }
            for (std::size_t i = 0; i < para.iterations; ++i) {
                sp.sp.setPosition({pos.x + size.x * i, pos.y});
                win.push_back(sp);
            }
        }
    }
}

}  // namespace sfml
}  // namespace addon
