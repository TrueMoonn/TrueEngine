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

EntitySpec::EntitySpec(ECS::Registry& reg) : te::APlugin(reg) {
    reg.registerComponent<te::Health>();
    _components["health"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float health = params["amount"].value_or(0.f);
            reg.addComponent(e, te::Health(health));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-health): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<te::Damage>();
    _components["damage"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float damage = params["amount"].value_or(0.f);
            reg.addComponent(e, te::Damage(damage));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-damage): " <<
                e.what() << std::endl;
        }
    };
    _systems["deal_damage"] = [](ECS::Registry& reg) {
        reg.addSystem(&te::deal_damage);
    };
}
