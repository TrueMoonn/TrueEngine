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

#include "Display.hpp"
#include "display/factory.hpp"

Display::Display(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Drawable>();
    _components["drawable"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        (void)params;
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

    reg.registerComponent<te::Animation>();
    _components["animation"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            std::vector<te::FrameData> frames;
            const auto &toml_frames = params["frames"].as_array();
            for (size_t i = 0; i < toml_frames->size(); i++) {
                const auto &cur = toml_frames->at(0).as_array();

                te::pos pos = {cur->at(0).as_array()->at(0).value_or<size_t>(0),
                    cur->at(0).as_array()->at(0).value_or<size_t>(0)};
                size_t max = cur->at(1).value_or(0);
                float delta = cur->at(2).value_or(0.1f);
                bool loop = cur->at(3).value_or<float>(true);
                std::cout << *cur << std::endl;
                std::cout << pos[0] << " " << pos[1] << " " << max << "  " << delta << " "  << loop << std::endl;
                frames.push_back(te::FrameData{pos, max, delta, loop});
            }
            reg.addComponent(e, te::Animation(frames));
        } catch (const std::out_of_range&) {
            std::cerr << "error(Plugin-Animation): key not found" << std::endl;
        } catch (const toml::parse_error& e) {
            std::cerr << e.what() << std::endl;
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

    _systems["animate"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::animate);
    };
}
