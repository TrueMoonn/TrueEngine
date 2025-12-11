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

namespace addon {
namespace display {

void animate(ECS::Registry& reg) {
    auto& animations = reg.getComponents<Animation>();
    auto& sprites = reg.getComponents<sfml::Sprite>();
    auto cur = NOW;

    for (auto &&[an, sp] : ECS::Zipper(animations, sprites)) {
        if (an.timestamp.checkDelay(true)) {
            an.increment();
            auto rect = sp.getTextureRect();
            rect.position.y = rect.size.y * an.getCurrentAnim().frameBEG.y;
            rect.position.x = (rect.size.x * an.getCurrentAnim().frameBEG.x)
                + (rect.size.x * an.curFrame);
            sp.setTextureRect(rect);
        }
    }
}

}  // namespace display
}  // namespace addon
