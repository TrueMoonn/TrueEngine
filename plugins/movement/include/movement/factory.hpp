/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.hpp
*/

#pragma once

    #include <memory>

    #include <ECS/Registry.hpp>
    #include "EventManager.hpp"
    #include "plugin/APlugin.hpp"


class Movement : public te::APlugin {
 public:
    explicit Movement(ECS::Registry& reg, te::EventManager& events);
};

extern "C" {
    std::unique_ptr<Movement> get_pfactory(ECS::Registry& reg,
        te::EventManager& events) {
        return std::make_unique<Movement>(reg, events);
    }
}
