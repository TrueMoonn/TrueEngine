/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>

#include <toml++/toml.hpp>
#include <ECS/Zipper.hpp>

#include "movement/components/velocity.hpp"

#include "Interaction.hpp"
#include "interaction/factory.hpp"

Interaction::Interaction(ECS::Registry& reg, te::EventManager& events)
    : te::APlugin(reg, events) {
    reg.registerComponent<te::Interactive>();
    _components["interactive"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float left = params["left"].value_or(0.f);
            float top = params["top"].value_or(0.f);
            float width = params["width"].value_or(0.f);
            float height = params["height"].value_or(0.f);
            reg.addComponent(e, te::Interactive(
                left, top, width, height));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Interactive): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Player>();
    _components["player"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            (void)params;
            reg.addComponent(e, te::Player());
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Player): " <<
                e.what() << std::endl;
        }
    };
    events.addSubscription(te::System::KeyPressed, [](ECS::Registry& reg,
        const te::EventManager::eventContent& content){
        auto& event = std::get<te::KeysEvent>(content);
        auto& velocities = reg.getComponents<te::Velocity2>();
        auto& player = reg.getComponents<te::Player>();

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
    _systems["player_interaction"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::player_interaction_sys);
    };
}

