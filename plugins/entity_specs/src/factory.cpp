/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>
#include <toml++/toml.hpp>

#include "EntitySpec.hpp"
#include "entity_spec/factory.hpp"

namespace addon {
namespace eSpec {

EntitySpec::EntitySpec(ECS::Registry& reg, te::event::EventManager& events)
    : te::plugin::APlugin(reg, events) {
    reg.registerComponent<Health>();
    _components["health"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float health = params["amount"].value_or(0.f);
            reg.createComponent<Health>(e, health);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-health): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Team>();
    _components["team"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            size_t damage = params["team"].value_or(0);
            reg.createComponent<Team>(e, damage);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-team): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Damage>();
    _components["damage"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float damage = params["amount"].value_or(0.f);
            reg.createComponent<Damage>(e, damage);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-damage): " <<
                e.what() << std::endl;
        }
    };
    _systems["deal_damage"] = [](ECS::Registry& reg) {
        reg.addSystem(&deal_damage);
    };
    _systems["kill_entity"] = [](ECS::Registry& reg) {
        reg.addSystem(&kill_entity);
    };
}

}  // namespace eSpec
}  // namespace addon
