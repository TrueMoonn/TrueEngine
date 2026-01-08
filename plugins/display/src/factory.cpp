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

#include <ECS/Entity.hpp>
#include <ECS/Registry.hpp>
#include <ECS/DenseZipper.hpp>
#include <maths/Vector.hpp>

#include "sfml/components/sprite.hpp"

#include "Display.hpp"
#include "display/factory.hpp"

namespace addon {
namespace display {

Display::Display(ECS::Registry& reg, te::SignalManager& sig)
    : te::plugin::APlugin(reg, sig) {
    reg.registerComponent<Parallax>();
    _components["parallax"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            const auto &reset = params["reset"].as_array();
            mat::Vector2i resetPos = {
                reset->at(0).value_or(0),
                reset->at(1).value_or(0)
            };
            reg.createComponent<Parallax>(
                e, params["iteration"].value_or(1), resetPos);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Parallax): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Animation>();
    _components["animation"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            std::vector<FrameData> frames;
            const auto &toml_frames = params["frames"].as_array();
            for (size_t i = 0; i < toml_frames->size(); i++) {
                const auto &cur = toml_frames->at(i).as_array();
                mat::Vector2<size_t> pos = {
                    cur->at(0).as_array()->at(0).value_or<size_t>(0),
                    cur->at(0).as_array()->at(1).value_or<size_t>(0)
                };
               std::size_t max = cur->at(1).value_or(0);
                float delta = cur->at(2).value_or(0.1f);
                bool loop = cur->at(3).value_or(true);
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
        reg.addSystem([](ECS::Registry& reg){
            auto& animations = reg.getComponents<Animation>();
            auto& sprites = reg.getComponents<sfml::Sprite>();
            auto cur = NOW;

            for (auto &&[an, sp] : ECS::DenseZipper(animations, sprites)) {
                if (an.timestamp.checkDelay(true)) {
                    an.increment();
                    auto rect = sp.sp.getTextureRect();
                    rect.position.y =
                        rect.size.y * an.getCurrentAnim().frameBEG.y;
                    rect.position.x =
                        (rect.size.x * an.getCurrentAnim().frameBEG.x)
                        + (rect.size.x * an.curFrame);
                    sp.sp.setTextureRect(rect);
                }
            }
        });
    };
}

}  // namespace display
}  // namespace addon
