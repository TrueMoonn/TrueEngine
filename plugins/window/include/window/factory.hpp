/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.hpp
*/

#pragma once

    #include <unordered_map>
    #include <string>
    #include <functional>
    #include <any>
    #include <memory>

    #include <ECS/Registry.hpp>
    #include "plugin/APlugin.hpp"


class Window : public APlugin {
 public:
    Window(ECS::Registry& reg);
};

extern "C" {
    std::unique_ptr<Window> get_pfactory(ECS::Registry& reg) {
        return std::make_unique<Window>(reg);
    }
}
