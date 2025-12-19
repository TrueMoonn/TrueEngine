/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>
#include <toml++/toml.hpp>
#include <ECS/Registry.hpp>
#include <SignalManager.hpp>

#include <ECS/Zipper.hpp>
#include <clock.hpp>

#include "Physic.hpp"
#include "physic/factory.hpp"

namespace addon {
namespace physic {

Physic::Physic(ECS::Registry& reg, te::SignalManager& sig)
    : te::plugin::APlugin(reg, sig) {
    reg.registerComponent<Position2>();
    _components["position2"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float x = params["x"].value_or(0.f);
            float y = params["y"].value_or(0.f);
            reg.createComponent<Position2>(e, x, y);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Position2): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Velocity2>();
    _components["velocity2"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float x = params["x"].value_or(0.f);
            float y = params["y"].value_or(0.f);
            reg.createComponent<Velocity2>(e, x, y);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Velocity2): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Hitbox>();
    _components["hitbox"] = [](ECS::Registry& reg, const ECS::Entity& e,
        const toml::table& params) {
        try {
            float left = params["left"].value_or(0.f);
            float top = params["top"].value_or(0.f);
            float width = params["width"].value_or(0.f);
            float height = params["height"].value_or(0.f);
            reg.createComponent<Hitbox>(e, left, top, width, height);
        } catch (const std::bad_any_cast& e) {
            std::cerr << "error(Plugin-Hitbox): " <<
                e.what() << std::endl;
        }
    };
    reg.registerComponent<Movable>();
    _components["movable"] = [](ECS::Registry& reg, const ECS::Entity& e,
            const toml::table&) {
        reg.createComponent<Movable>(e);
    };
    reg.registerComponent<Stationary>();
    _components["stationary"] = [](ECS::Registry& reg, const ECS::Entity& e,
            const toml::table&) {
        reg.createComponent<Stationary>(e);
    };
    _systems["movement2"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry& reg) {
            static te::Timestamp delta(0.f);
            auto& positions = reg.getComponents<Position2>();
            auto& velocities = reg.getComponents<Velocity2>();

            float elapsed = delta.getElapsedTime();
            for (auto&&[pos, vel] : ECS::Zipper(positions, velocities)) {
                pos.x += vel.x * elapsed / 1000000;
                pos.y += vel.y * elapsed / 1000000;
            }
            delta.restart();
        });
    };
    _systems["bound_hitbox"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry& reg) {
            auto& positions = reg.getComponents<Position2>();
            auto& velocities = reg.getComponents<Velocity2>();
            auto& hitboxs = reg.getComponents<Hitbox>();
            auto& movable = reg.getComponents<Movable>();

            for (auto &&[id, pos, vel, hit, mov]
                : ECS::IndexedZipper(positions, velocities, hitboxs, movable)) {
                for (ECS::Entity cmp : entity_hit(reg, id)) {
                    auto e_pos = reg.getComponents<Position2>()[cmp].value();
                    auto e_hit = reg.getComponents<Hitbox>()[cmp].value();

                    float dx = (pos.x + hit.size.x / 2) - (e_pos.x + e_hit.size.x / 2);
                    float px = (hit.size.x / 2 + e_hit.size.x / 2) - std::fabs(dx);

                    float dy = (pos.y + hit.size.y / 2) - (e_pos.y + e_hit.size.y / 2);
                    float py = (hit.size.y / 2 + e_hit.size.y / 2) - std::fabs(dy);

                    if (px < py)
                        pos.x += (dx < 0 ? -px : px);
                    else
                        pos.y += (dy < 0 ? -py : py);
                }
            }
        });
    };
}

}  // namespace physic
}  // namespace addon
