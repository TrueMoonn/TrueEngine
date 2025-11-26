/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** display.cpp
*/

#include <ECS/Zipper.hpp>

#include "display/systems/display.hpp"

#include "components/window.hpp"

namespace te {

void display_sys(ECS::Registry& reg) {
    auto& windows = reg.getComponents<Window>();

    for (auto &&[win] : ECS::Zipper(windows)) {
        win.value().display();
        win.value().clear();
    }
}

}  // namespace te
