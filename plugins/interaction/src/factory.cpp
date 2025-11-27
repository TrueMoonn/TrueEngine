/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include "Interaction.hpp"
#include "interaction/factory.hpp"

Interaction::Interaction(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Interactive>();
    _components["interactive"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const te::json_like json) {
        try {
            te::interactive_func func = [](ECS::Registry&){};
            if (json.find("func") != json.end()) {
                func = std::any_cast<te::interactive_func>(json.at("func"));
            }
            if (json.find("rect") != json.end()) {
                sf::FloatRect rect =
                    std::any_cast<sf::FloatRect>(json.at("rect"));
                reg.addComponent(e, te::Interactive(rect, func));
                return;
            }
            float left = std::any_cast<float>(json.at("left"));
            float top = std::any_cast<float>(json.at("top"));
            float width = std::any_cast<float>(json.at("width"));
            float height = std::any_cast<float>(json.at("height"));
            reg.addComponent(e, te::Interactive(left, top, width, height, func));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Interactive): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Player>();
    _components["player"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const te::json_like json) {
        try {
            (void)json;
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

