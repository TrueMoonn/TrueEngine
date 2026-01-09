/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.cpp
*/

#include <iostream>
#include <vector>
#include <string>
#include <toml++/toml.hpp>

#include <ECS/Registry.hpp>
#include <ECS/DenseZipper.hpp>
#include <ECS/Entity.hpp>
#include <maths/Rect.hpp>
#include <maths/Vector.hpp>

#include "ECS/DenseSA.hpp"
#include "physic/components/hitbox.hpp"
#include "physic/components/velocity.hpp"
#include "physic/components/position.hpp"

#include "EntitySpec.hpp"
#include "entity_spec/factory.hpp"

namespace addon {
namespace eSpec {

static bool square_hitbox(mat::RectF rect1, mat::RectF rect2) {
    return (rect1.position.x < rect2.position.x + rect2.size.x &&
        rect1.position.x + rect1.size.x > rect2.position.x &&
        rect1.position.y < rect2.position.y + rect2.size.y &&
        rect1.position.y + rect1.size.y > rect2.position.y);
}

static mat::RectF true_hitbox(const physic::Position2 &pos,
    const physic::Hitbox &hit) {
    return mat::RectF(
        mat::Vector2f(pos.x + hit.position.x, pos.y + hit.position.y),
        mat::Vector2f(hit.size.x, hit.size.y));
}

static std::vector<ECS::Entity> entity_hit_team(ECS::Registry& reg,
    const ECS::Entity& entity) {
    std::vector<ECS::Entity> entities_hit;

    auto& positions = reg.getComponents<physic::Position2>();
    auto& hitboxs = reg.getComponents<physic::Hitbox>();
    auto& teams = reg.getComponents<Team>();
    auto& damage = reg.getComponents<Damage>();

    auto e_hit = true_hitbox(GET_ENTITY_CMPT(positions, entity),
        GET_ENTITY_CMPT(hitboxs, entity));
    auto& e_team = GET_ENTITY_CMPT(teams, entity);

    for (auto &&[e, pos, hit, tm, _]
        : ECS::IndexedDenseZipper(positions, hitboxs, teams, damage)) {
        if (tm.name == e_team.name)
            continue;
        if (square_hitbox(e_hit, true_hitbox(pos, hit)))
            entities_hit.push_back(e);
    }
    return entities_hit;
}

EntitySpec::EntitySpec(ECS::Registry& reg, te::SignalManager& sig)
    : te::plugin::APlugin(reg, sig) {
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
           std::size_t type = params["type"].value_or<size_t>(1);
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
    _systems["deal_damage"] = [&sig](ECS::Registry& reg) {
        reg.addSystem([&sig](ECS::Registry& reg) {
            auto &hit = reg.getComponents<physic::Hitbox>();
            auto &pos = reg.getComponents<physic::Position2>();
            auto &health = reg.getComponents<Health>();
            auto &damage = reg.getComponents<Damage>();
            auto &team = reg.getComponents<Team>();
            std::vector<ECS::Entity> deads;

            for (auto &&[id, _, __, hp, tm]
                : ECS::IndexedDenseZipper(hit, pos, health, team)) {
                if (!hp.delay.isPaused()) {
                    if (hp.delay.checkDelay())
                        hp.delay.toggle();
                    else
                        continue;
                }
                for (auto &hit : entity_hit_team(reg, id)) {
                    hp.reduceSafely(GET_ENTITY_CMPT(damage, hit).amount);
                    hp.delay.toggle();
                    if (hp.amount <= 0)
                        deads.push_back(id);
                }
            }
            for (auto& e : deads)
                sig.emit("no_health_entity", e);
        });
    };
    _systems["kill_timeout"] = [&sig](ECS::Registry& reg) {
        reg.addSystem([&sig](ECS::Registry& reg) {
            auto& timeouts = reg.getComponents<Timeout>();
            for (auto &&[id, to] : ECS::IndexedDenseZipper(timeouts))
                if (to.delta.checkDelay(false))
                    sig.emit("timout_entity", id);
        });
    };
    _systems["apply_pattern"] = [](ECS::Registry& reg) {
        reg.addSystem([](ECS::Registry &reg) {
            auto &velocity = reg.getComponents<physic::Velocity2>();
            auto &position = reg.getComponents<physic::Position2>();
            auto &pattern = reg.getComponents<Pattern>();

            for (auto &&[vel, _, pat] :
                ECS::DenseZipper(velocity, position, pattern))
                vel.y = pat.func(pat.frequency) * pat.amplitude;
        });
    };
    _systems["apply_fragile"] = [&sig](ECS::Registry& reg) {
        reg.addSystem([&sig](ECS::Registry& reg){
            auto &hitbox = reg.getComponents<physic::Hitbox>();
            auto &position = reg.getComponents<physic::Position2>();
            auto &fragile = reg.getComponents<Fragile>();
            auto &robust = reg.getComponents<Robust>();
            std::vector<ECS::Entity> deads;

            for (auto &&[e_id, e_pos, e_hit, e_frag]
                    : ECS::IndexedDenseZipper(position, hitbox, fragile)) {
                auto e_truehit = true_hitbox(e_pos, e_hit);
                for (auto &&[id, pos, hit, rob]
                        : ECS::IndexedDenseZipper(position, hitbox, robust)) {
                    if (e_id == id || e_frag.priority >= rob.priority ||
                        !square_hitbox(e_truehit, true_hitbox(pos, hit)))
                        continue;
                    e_frag.destroyed = true;
                    deads.push_back(e_id);
                    break;
                }
            }
            for (auto& e : deads)
                sig.emit("broken_entity", e);
        });
    };
}

}  // namespace eSpec
}  // namespace addon
