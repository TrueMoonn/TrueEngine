/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include "movement/components/position.hpp"
#include "movement/components/velocity.hpp"
#include "movement/systems/movement.hpp"

#include "movement/factory.hpp"

Movement::Movement(ECS::Registry& reg) : APlugin(reg) {
    reg.registerComponent<te::Position2>();
    _builders[typeid(te::Position2)] = [](const ECS::Entity& e,
        ECS::Registry& reg, const json_like json) {
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
    _builders[typeid(te::Velocity2)] = [](const ECS::Entity& e,
        ECS::Registry& reg, const json_like json) {
        try {
            float x = std::any_cast<float>(json.at("x"));
            float y = std::any_cast<float>(json.at("y"));
            reg.addComponent(e, te::Velocity2(x, y));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Velocity2): " <<
                e.what() << std::endl;
        }
    };
    reg.addSystem(&te::movement2_sys);
}
