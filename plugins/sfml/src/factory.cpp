/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <string>
#include <utility>
#include <iostream>
#include <SFML/System/Exception.hpp>
#include <toml++/toml.hpp>

#include "Sfml.hpp"
#include "sfml/factory.hpp"

Sfml::Sfml(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Event>();
    _components["event_manager"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        reg.addComponent(e, te::Event());
    };
    reg.registerComponent<te::Window>();
    _components["window"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.addComponent(e, te::Window());
    };
    reg.registerComponent<te::Drawable>();
    _components["drawable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.addComponent(e, te::Drawable());
    };
    reg.registerComponent<te::Sprite>();
    _components["sprite"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            sf::Texture texture(params["path"].value_or(""));
            sf::Vector2f size(
                params["width"].value_or(50.0),
                params["height"].value_or(50.0));
            sf::Vector2f scale(size.x / texture.getSize().x,
                size.y / texture.getSize().y);
            reg.addComponent(e, te::Sprite(std::move(texture), scale));
        } catch (const std::out_of_range&) {
            std::cerr << "error(Plugin-Sprite): key not found" << std::endl;
        } catch (const sf::Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    };

    _systems["events"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::manageEvent);
    };
    _systems["display"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::display_sys);
    };
    _systems["draw"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::draw_sys);
    };
    _systems["follow_player"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::follow_player_sys);
    };

}
