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


class EntitySpec : public te::APlugin {
 public:
    explicit EntitySpec(ECS::Registry& reg);
};

extern "C" {
    std::unique_ptr<EntitySpec> get_pfactory(ECS::Registry& reg) {
        return std::make_unique<EntitySpec>(reg);
    }
}
