/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>

#include <toml++/toml.hpp>

#include "Interaction.hpp"
#include "interaction/factory.hpp"

Interaction::Interaction(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Player>();
    _components["player"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            (void)params;
            reg.createComponent<te::Player>(e);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Player): " <<
                e.what() << std::endl;
        }
    };
}

