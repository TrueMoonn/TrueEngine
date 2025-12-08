/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>
#include <toml++/toml.hpp>

#include "Physic.hpp"
#include "physic/factory.hpp"

Physic::Physic(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Position2>();
    _components["position2"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float x = params["x"].value_or(0.f);
            float y = params["y"].value_or(0.f);
            reg.createComponent<te::Position2>(e, x, y);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Position2): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Velocity2>();
    _components["velocity2"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float x = params["x"].value_or(0.f);
            float y = params["y"].value_or(0.f);
            reg.createComponent<te::Velocity2>(e, x, y);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Velocity2): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Hitbox>();
    _components["hitbox"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float left = params["left"].value_or(0.f);
            float top = params["top"].value_or(0.f);
            float width = params["width"].value_or(0.f);
            float height = params["height"].value_or(0.f);
            reg.createComponent<te::Hitbox>(e, left, top, width, height);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Hitbox): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Movable>();
    _components["movable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            (void)params;
            reg.createComponent<te::Movable>(e);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Movable): " <<
                e.what() << std::endl;
        }
    };
    _systems["movement2"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::movement2_sys);
    };
    _systems["bound_hitbox"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::hitbox2_sys);
    };
}
