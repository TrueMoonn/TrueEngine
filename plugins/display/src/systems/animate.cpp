/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** animate
*/

#include <ECS/Zipper.hpp>

#include "clock.hpp"

#include "display/systems/animate.hpp"

#include "sfml/components/sprite.hpp"
#include "display/components/animation.hpp"

namespace te {

void animate(ECS::Registry& reg) {
    auto& animations = reg.getComponents<Animation>();
    auto& sprites = reg.getComponents<Sprite>();
    auto cur = NOW;

    // std::cout << cur << " - " << "anim" << std::endl;
    for (auto &&[an, sp] : ECS::Zipper(animations, sprites)) {
        if (CAST_M(cur, V(an).delta) > V(an).getCurrentAnim().frameDELAY) {
            auto rect = V(sp).getTextureRect();
            V(an).delta = cur;
            V(an).increment();
            rect.position.x = rect.size.x * V(an).curFrame;
            V(sp).setTextureRect(rect);
        }
    }
}

}  // namespace te
