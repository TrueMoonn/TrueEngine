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

Interaction::Interaction(ECS::Registry& reg, te::event::EventManager& events)
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
    events.addSubscription(te::event::System::KeyPressed,
        [](ECS::Registry& reg,
        const te::event::EventManager::eventContent& content){
        auto& event = std::get<te::event::KeysEvent>(content);
        auto& velocities = reg.getComponents<physic::Velocity2>();
        auto& player = reg.getComponents<Player>();

        for (auto&& [vel, play] : ECS::Zipper(velocities, player)) {
            if (event.keys[te::event::Key::Z])
                vel.y = -3.0;
            else if (event.keys[te::event::Key::S])
                vel.y = 3.0;
            else
                vel.y = 0.0;
            if (event.keys[te::event::Key::Q])
                vel.x = -3.0;
            else if (event.keys[te::event::Key::D])
                vel.x = 3.0;
            else
                vel.x = 0.0;
        }
    });
}

}  // namespace intact
}  // namespace addon
