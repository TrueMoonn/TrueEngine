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


class Display : public te::APlugin {
 public:
    explicit Display(ECS::Registry& reg);
};

extern "C" {
    std::unique_ptr<Display> get_pfactory(ECS::Registry& reg) {
        return std::make_unique<Display>(reg);
    }
}
