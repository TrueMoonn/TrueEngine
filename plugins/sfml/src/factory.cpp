/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <SFML/System/Exception.hpp>
#include <toml++/toml.hpp>

#include "Sfml.hpp"
#include "maths/Vector.hpp"
#include "sfml/components/window.hpp"
#include "sfml/events.hpp"
#include "sfml/factory.hpp"

namespace addon {
namespace sfml {

Sfml::Sfml(ECS::Registry& reg, te::event::EventManager& events)
    : te::plugin::APlugin(reg, events) {
    events.setPollFunc(&pollEvent);
    reg.registerComponent<Window>();
    _components["window"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        if (!params.empty()) {
            const auto& wName = params["name"].value_or(DEFAULT_WIN_NAME);
            const auto& size = params["size"].as_array();
            mat::Vector2u sizeVect;
            sizeVect.x = size->at(0).value_or(1280);
            sizeVect.y = size->at(1).value_or(720);
            const auto& fps =
                params["framelimit"].value_or(DEFAULT_FRAME_LIMIT);
            reg.createComponent<Window>(e, wName, sizeVect, fps);
        } else  {
            reg.createComponent<Window>(e);
        }
    };
    reg.registerComponent<Drawable>();
    _components["drawable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.createComponent<Drawable>(e);
    };
    reg.registerComponent<Sprite>();
    _components["sprite"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        static std::unordered_map<std::string, sf::Texture> textures;
        try {
            const auto& path = params["path"].value_or("");
            auto [it, inserted] = textures.try_emplace(path);
            if (inserted)
                it->second.loadFromFile(path);
            auto& texture = it->second;
            const auto &layer = params["layer"].value_or(0);
            const auto &t_size = params["size"].as_array();
            sf::Vector2i size = t_size ?
                sf::Vector2i(t_size->at(0).value_or(1),
                t_size->at(1).value_or(1)) : sf::Vector2i(texture.getSize());
            auto t_scale = params["scale"].as_array();
            sf::Vector2f scale = t_scale ?
                sf::Vector2f{t_scale->at(0).value_or(1.0f) / size.x,
                t_scale->at(1).value_or(1.0f) / size.y} : sf::Vector2f{1, 1};
            reg.createComponent<Sprite>(e, texture,
                layer, size, scale);
        } catch (const std::out_of_range&) {
            std::cerr << "error(Plugin-Sprite): key not found" << std::endl;
        } catch (const sf::Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    };
    _systems["display"] = [](ECS::Registry& reg) {
        reg.addSystem(&display_sys);
    };
    _systems["draw"] = [](ECS::Registry& reg) {
        reg.addSystem(&draw_sys);
    };
    _systems["follow_player"] = [](ECS::Registry& reg) {
        reg.addSystem(&follow_player_sys);
    };
    _systems["paralax_sys"] = [](ECS::Registry& reg) {
        reg.addSystem(&paralax_sys);
    };
}

}  // namespace sfml
}  // namespace addon
