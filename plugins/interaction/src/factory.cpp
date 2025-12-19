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

Interaction::Interaction(ECS::Registry& reg, te::SignalManager& sig)
    : te::plugin::APlugin(reg, sig) {
    reg.registerComponent<Player>();
    _components["player"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table&) {
        try {
            reg.createComponent<Player>(e);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Player): " <<
                e.what() << std::endl;
        }
    };
    // events.addSubscription(te::event::System::KeyPressed,
    //     [](ECS::Registry& reg,
    //     const te::event::EventManager::eventContent& content,
    //     std::optional<ECS::Entity> target_entity) {
    //     try {
    //         auto& event = std::get<te::event::KeysEvent>(content);
    //         auto& velocities = reg.getComponents<physic::Velocity2>();
    //         auto& players = reg.getComponents<Player>();

    //         if (!target_entity.has_value()) {
    //             for (auto&& [vel, play] : ECS::Zipper(velocities, players)) {
    //                 Interaction::updateVel(event, vel);
    //             }
    //         } else {
    //             ECS::Entity entity_id = target_entity.value();
    //             if (entity_id < velocities.size()
    //                 && velocities[entity_id].has_value()) {
    //                 auto& vel = velocities[entity_id].value();
    //                 Interaction::updateVel(event, vel);
    //             }
    //         }
    //     } catch (const std::bad_variant_access& e) {
    //         std::cerr << "error(Plugin-Interaction): Bad variant access - "
    //                   << e.what() << std::endl;
    //     }
    // });
}

}  // namespace intact
}  // namespace addon
