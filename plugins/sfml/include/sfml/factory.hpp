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


class Sfml : public te::APlugin {
 public:
    explicit Sfml(ECS::Registry& reg);
};

extern "C" {
    std::unique_ptr<Sfml> get_pfactory(ECS::Registry& reg) {
        return std::make_unique<Sfml>(reg);
    }
}
