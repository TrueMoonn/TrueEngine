/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.hpp
*/

#pragma once

    #include <memory>

    #include <ECS/Registry.hpp>
    #include "plugin/APlugin.hpp"


class Display : public te::plugin::APlugin {
 public:
    explicit Display(ECS::Registry& reg, te::EventManager& events);
};

extern "C" {
    std::unique_ptr<Display> get_pfactory(ECS::Registry& reg,
        te::EventManager& events) {
        return std::make_unique<Display>(reg, events);
    }
}
