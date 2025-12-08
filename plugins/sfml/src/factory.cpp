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
#include "sfml/events.hpp"
#include "sfml/factory.hpp"

Sfml::Sfml(ECS::Registry& reg, te::EventManager& events)
    : te::plugin::APlugin(reg, events) {
    events.setPollFunc(&pollEvent);
    reg.registerComponent<te::Window>();
    _components["window"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.createComponent<te::Window>(e);
    };
    reg.registerComponent<te::Drawable>();
    _components["drawable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.createComponent<te::Drawable>(e);
    };
    reg.registerComponent<te::Sprite>();
    _components["sprite"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            sf::Texture texture(params["path"].value_or(""));
            const auto &t_size = params["size"].as_array();
            sf::Vector2i size = t_size ?
                sf::Vector2i(t_size->at(0).value_or(1),
                t_size->at(1).value_or(1)) : sf::Vector2i(texture.getSize());
            auto t_scale = params["scale"].as_array();
            sf::Vector2f scale = t_scale ?
                sf::Vector2f{t_scale->at(0).value_or(1.0f) / size.x,
                t_scale->at(1).value_or(1.0f) / size.y} : sf::Vector2f{1, 1};
            reg.addComponent(e, te::Sprite(std::move(texture), size, scale));
        } catch (const std::out_of_range&) {
            std::cerr << "error(Plugin-Sprite): key not found" << std::endl;
        } catch (const sf::Exception& e) {
            std::cerr << e.what() << std::endl;
        }
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
