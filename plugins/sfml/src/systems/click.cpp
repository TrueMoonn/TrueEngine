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

void click_sys(ECS::Registry& reg) {
    // auto& windows = reg.getComponents<Window>();

    // for (auto &&[win] : ECS::Zipper(windows)) {
    //     win.display();
    //     win.clear();
    // } TODO FOR CLICK DONT ASK FOR CHANGES
}

}  // namespace sfml
}  // namespace addon
