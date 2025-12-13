/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** deal_damage
*/

#include <iostream>

#include <ECS/Zipper.hpp>

#include "entity_spec/systems/apply_pattern.hpp"
#include "entity_spec/components/pattern.hpp"

#include "physic/components/velocity.hpp"
#include "physic/components/position.hpp"

namespace addon {
namespace eSpec {

void apply_pattern(ECS::Registry &reg) {
    auto &velocity = reg.getComponents<physic::Velocity2>();
    auto &position = reg.getComponents<physic::Position2>();
    auto &pattern = reg.getComponents<Pattern>();

    for (auto &&[vel, _, pat] : ECS::Zipper(velocity, position, pattern))
        vel.y = pat.func(pat.frequency) * pat.amplitude;
}

}  // namespace eSpec
}  // namespace addon
