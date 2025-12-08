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
    reg.registerComponent<te::Interactive>();
    _components["interactive"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float left = params["left"].value_or(0.f);
            float top = params["top"].value_or(0.f);
            float width = params["width"].value_or(0.f);
            float height = params["height"].value_or(0.f);
            reg.addComponent(e, te::Interactive(
                left, top, width, height));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Interactive): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Player>();
    _components["player"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            (void)params;
            reg.addComponent(e, te::Player());
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Player): " <<
                e.what() << std::endl;
        }
    };
    _systems["player_interaction"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::player_interaction_sys);
    };
}

