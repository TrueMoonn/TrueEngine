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


class Interaction : public te::plugin::APlugin {
 public:
    explicit Interaction(ECS::Registry& reg, te::EventManager& events);
};

extern "C" {
    std::unique_ptr<Interaction> get_pfactory(ECS::Registry& reg,
        te::EventManager& events) {
        return std::make_unique<Interaction>(reg, events);
    }
}

