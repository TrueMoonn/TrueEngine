/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>

#include <toml++/toml.hpp>

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
}

}  // namespace intact
}  // namespace addon
