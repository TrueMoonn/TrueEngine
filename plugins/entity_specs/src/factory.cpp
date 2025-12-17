/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>
#include <string>
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
            float delay = params["delay"].value_or(0.f);
            reg.createComponent<Health>(e, health, delay);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-health): " << e.what() << std::endl;
        }
    };
    reg.registerComponent<Team>();
    _components["team"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            std::string name(params["name"].value_or(""));
            reg.createComponent<Team>(e, name);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-team): " << e.what() << std::endl;
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
    reg.registerComponent<Timeout>();
    _components["timeout"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float delay = params["duration"].value_or<float>(0.f);
            reg.createComponent<Timeout>(e, delay);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-timeout): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Pattern>();
    _components["pattern"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            size_t type = params["type"].value_or<size_t>(1);
            float amp = params["amplitude"].value_or<float>(1.f);
            float freq = params["frequency"].value_or<float>(1.f);
            reg.createComponent<Pattern>(e, type, amp, freq);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-pattern): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Fragile>();
    _components["fragile"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            std::size_t priority = params["priority"].value_or(1);
            reg.createComponent<Fragile>(e, priority);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-fragile): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Robust>();
    _components["robust"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            std::size_t priority = params["priority"].value_or(1);
            reg.createComponent<Robust>(e, priority);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-robust): " <<
                e.what() << std::endl;
        }
    };
    _systems["deal_damage"] = [](ECS::Registry& reg) {
        reg.addSystem(&deal_damage);
    };
    _systems["apply_pattern"] = [](ECS::Registry& reg) {
        reg.addSystem(&apply_pattern);
    };
    _systems["kill_entity"] = [](ECS::Registry& reg) {
        reg.addSystem(&kill_entity);
    };
    _systems["apply_fragile"] = [](ECS::Registry& reg) {
        reg.addSystem(&apply_fragile);
    };
}

}  // namespace eSpec
}  // namespace addon
