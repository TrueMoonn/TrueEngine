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
#include <ECS/Zipper.hpp>
#include <toml++/toml.hpp>

#include "Sfml.hpp"
#include "sfml/events.hpp"
#include "sfml/factory.hpp"

namespace addon {
namespace sfml {

Sfml::Sfml(ECS::Registry& reg, te::event::EventManager& events)
    : te::plugin::APlugin(reg, events) {
    events.setPollFunc(&pollEvent);
    reg.registerComponent<Window>();
    _components["window"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.createComponent<Window>(e);
    };
    reg.registerComponent<Drawable>();
    _components["drawable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.createComponent<Drawable>(e);
    };
    reg.registerComponent<Clickable>();
    _components["clickable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.createComponent<Clickable>(e);
    };
    reg.registerComponent<Hoverable>();
    _components["hoverable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        reg.createComponent<Hoverable>(e);
    };
    events.addSubscription(te::event::System::MouseButtonPressed,
        [&events](ECS::Registry& reg,
        const te::event::EventManager::eventContent& content,
        std::optional<ECS::Entity> e){
        auto &window = reg.getComponents<Window>();
        auto &sprite = reg.getComponents<Sprite>();
        auto& event = std::get<te::event::MouseEvent>(content);
        int i = 0;

        for (auto && [win] : ECS::Zipper(window)) {
            for (auto&& [spr] : ECS::Zipper(sprite)) {
                if (event._MouseKey.at(te::event::MouseButton::MouseLeft).active) {
                    const auto &pos = sf::Mouse::getPosition(win);
                    const auto &translated = win.mapPixelToCoords(pos);

                    if (spr.getGlobalBounds().contains(translated)) {
                        if (i == 1)
                            events.updateScene(9);
                        i++;
                    }
                }
            }
        }
    });
    reg.registerComponent<Sprite>();
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
            reg.addComponent(e, Sprite(std::move(texture), size, scale));
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
}

}  // namespace sfml
}  // namespace addon
