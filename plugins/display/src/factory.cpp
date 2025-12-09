/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Display plugin factory
*/

#include <string>
#include <utility>
#include <iostream>
#include <vector>

#include <SFML/System/Exception.hpp>
#include <toml++/toml.hpp>

#include "Display.hpp"
#include "display/factory.hpp"

namespace addon {
namespace display {

Display::Display(ECS::Registry& reg, te::event::EventManager& events)
    : te::plugin::APlugin(reg, events) {
    reg.registerComponent<Animation>();
    _components["animation"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            std::vector<FrameData> frames;
            const auto &toml_frames = params["frames"].as_array();
            for (size_t i = 0; i < toml_frames->size(); i++) {
                const auto &cur = toml_frames->at(0).as_array();
                pos pos = {cur->at(0).as_array()->at(0).value_or<size_t>(0),
                    cur->at(0).as_array()->at(0).value_or<size_t>(0)};
                size_t max = cur->at(1).value_or(0);
                float delta = cur->at(2).value_or(0.1f);
                bool loop = cur->at(3).value_or<float>(true);
                frames.push_back(FrameData{pos, max, delta, loop});
            }
            reg.addComponent(e, Animation(frames));
        } catch (const std::out_of_range&) {
            std::cerr << "error(Plugin-Animation): key not found" << std::endl;
        } catch (const toml::parse_error& e) {
            std::cerr << e.what() << std::endl;
        } catch (const sf::Exception& e) {
            std::cerr << e.what() << std::endl;
        }
    };
    _systems["animate"] = [](ECS::Registry& reg) {
        reg.addSystem(&animate);
    };
}

}  // namespace display
}  // namespace addon
