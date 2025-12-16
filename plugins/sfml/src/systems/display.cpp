/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** display.cpp
*/

#include <ECS/Zipper.hpp>

#include "sfml/components/window.hpp"
#include "sfml/systems/display.hpp"

namespace addon {
namespace sfml {

void display_sys(ECS::Registry& reg) {
    auto& windows = reg.getComponents<Window>();

    for (auto &&[win] : ECS::Zipper(windows)) {
        for (std::size_t i = 0; i < win.draws.size(); ++i) {
            for (auto& sprite : win.draws[i]) {
                win.draw(sprite.sp);
            }
            win.draws[i].clear();
        }
        win.display();
        win.clear();
    }
}

}  // namespace sfml
}  // namespace addon
