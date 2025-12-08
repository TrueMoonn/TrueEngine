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


class Physic : public te::plugin::APlugin {
 public:
    explicit Physic(ECS::Registry& reg, te::EventManager& events);
};

extern "C" {
    std::unique_ptr<Physic> get_pfactory(ECS::Registry& reg,
        te::EventManager& events) {
        return std::make_unique<Physic>(reg, events);
    }
}
