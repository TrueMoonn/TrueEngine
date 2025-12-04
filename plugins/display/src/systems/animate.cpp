/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** animate
*/

#include <ECS/Zipper.hpp>

#include "display/systems/animate.hpp"

#include "display/components/sprite.hpp"
#include "display/components/animation.hpp"

#define V(a) a.value()

namespace te {

void animate(ECS::Registry& reg) {
    auto& animations = reg.getComponents<Animation>();
    auto& sprites = reg.getComponents<Sprite>();
    auto cur = std::clock();

    for (auto &&[an, sp] : ECS::Zipper(animations, sprites)) {
        if (cur - V(an).delta > V(an).getCurrentAnim().frameDELAY) {
            V(an).delta = cur;
            V(an).increment();
            std::cout << "Currently at frame " << V(an).curFrame << " of anim "
            << V(an).curAnim << std::endl;
        }
    }
}

}  // namespace te
