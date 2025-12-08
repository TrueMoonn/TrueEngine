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

namespace addon {
namespace physic {

Physic::Physic(ECS::Registry& reg, te::event::EventManager& events)
    : te::plugin::APlugin(reg, events) {
    reg.registerComponent<Position2>();
    _components["position2"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float x = params["x"].value_or(0.f);
            float y = params["y"].value_or(0.f);
            reg.createComponent<Position2>(e, x, y);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Position2): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Velocity2>();
    _components["velocity2"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float x = params["x"].value_or(0.f);
            float y = params["y"].value_or(0.f);
            reg.createComponent<Velocity2>(e, x, y);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Velocity2): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Hitbox>();
    _components["hitbox"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float left = params["left"].value_or(0.f);
            float top = params["top"].value_or(0.f);
            float width = params["width"].value_or(0.f);
            float height = params["height"].value_or(0.f);
            reg.createComponent<Hitbox>(e, left, top, width, height);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Hitbox): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Movable>();
    _components["movable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            (void)params;
            reg.createComponent<Movable>(e);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Movable): " <<
                e.what() << std::endl;
        }
    };
    _systems["movement2"] = [](ECS::Registry& reg) {
        reg.addSystem(&movement2_sys);
    };
    _systems["bound_hitbox"] = [](ECS::Registry& reg) {
        reg.addSystem(&hitbox2_sys);
    };
}

}  // namespace physic
}  // namespace addon
