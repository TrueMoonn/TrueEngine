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

#include "Display.hpp"
#include "display/factory.hpp"

Display::Display(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Drawable>();
    _components["drawable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const te::json_like json) {
        (void)json;
        reg.addComponent(e, te::Drawable());
    };
    reg.registerComponent<te::Sprite>();
    _components["sprite"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const te::json_like json) {
        try {
            if (json.find("texture") != json.end()) {
                sf::Texture texture =
                    std::any_cast<sf::Texture>(json.at("texture"));
                reg.addComponent(e, te::Sprite(std::move(texture)));
                return;
            }
            std::filesystem::path path(
                std::any_cast<std::string>(json.at("path")));
            sf::Texture texture(path);
            if (json.find("size") != json.end()) {
                sf::Vector2f size =
                    std::any_cast<sf::Vector2f>(json.at("size"));
                sf::Vector2f scale(size.x / texture.getSize().x,
                    size.y / texture.getSize().y);
                reg.addComponent(e, te::Sprite(std::move(texture), scale));
            } else {
                reg.addComponent(e, te::Sprite(std::move(texture)));
            }
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Sprite): " <<
                e.what() << std::endl;
        } catch (const std::out_of_range&) {
            std::cerr << "error(Plugin-Sprite): key not found" << std::endl;
        } catch (const sf::Exception& e) {}
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
