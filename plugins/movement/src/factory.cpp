/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>

#include "Movement.hpp"
#include "movement/factory.hpp"

Movement::Movement(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Position2>();
    _components["position2"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const te::json_like json) {
        try {
            float x = std::any_cast<float>(json.at("x"));
            float y = std::any_cast<float>(json.at("y"));
            reg.addComponent(e, te::Position2(x, y));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Position2): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Velocity2>();
    _components["velocity2"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const te::json_like json) {
        try {
            float x = std::any_cast<float>(json.at("x"));
            float y = std::any_cast<float>(json.at("y"));
            reg.addComponent(e, te::Velocity2(x, y));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Velocity2): " <<
                e.what() << std::endl;
        }
    };
    _systems["movement2"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::movement2_sys);
    };
}
