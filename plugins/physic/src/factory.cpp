/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>

#include "Physics.hpp"
#include "physic/factory.hpp"

Physic::Physic(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Hitbox>();
    _components["hitbox"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const te::json_like json) {
        try {
            if (json.find("rect") != json.end()) {
                sf::FloatRect rect =
                    std::any_cast<sf::FloatRect>(json.at("rect"));
                reg.addComponent(e, te::Hitbox(rect));
                return;
            }
            float left = std::any_cast<float>(json.at("left"));
            float top = std::any_cast<float>(json.at("top"));
            float width = std::any_cast<float>(json.at("width"));
            float height = std::any_cast<float>(json.at("height"));
            reg.addComponent(e, te::Hitbox(left, top, width, height));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Hitbox): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Movable>();
    _components["movable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const te::json_like json) {
        try {
            (void)json;
            reg.addComponent(e, te::Movable());
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Movable): " <<
                e.what() << std::endl;
        }
    };
    _systems["bound_hitbox"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::hitbox2_sys);
    };
}
