/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>

#include <toml++/toml.hpp>
#include <ECS/Zipper.hpp>

#include "physic/components/velocity.hpp"

#include "Interaction.hpp"
#include "interaction/factory.hpp"

namespace addon {
namespace intact {

Interaction::Interaction(ECS::Registry& reg, te::EventManager& events)
    : te::plugin::APlugin(reg, events) {
    reg.registerComponent<Player>();
    _components["player"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            (void)params;
            reg.createComponent<Player>(e);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Player): " <<
                e.what() << std::endl;
        }
    };
    events.addSubscription(te::System::KeyPressed, [](ECS::Registry& reg,
        const te::EventManager::eventContent& content){
        auto& event = std::get<te::KeysEvent>(content);
        auto& velocities = reg.getComponents<physic::Velocity2>();
        auto& player = reg.getComponents<Player>();

        for (auto&& [vel, play] : ECS::Zipper(velocities, player)) {
            if (event.keys[te::Key::Z])
                vel.value().y = -3.0;
            else if (event.keys[te::Key::S])
                vel.value().y = 3.0;
            else
                vel.value().y = 0.0;
            if (event.keys[te::Key::Q])
                vel.value().x = -3.0;
            else if (event.keys[te::Key::D])
                vel.value().x = 3.0;
            else
                vel.value().x = 0.0;
        }
    });
}

}  // namespace intact
}  // namespace addon
