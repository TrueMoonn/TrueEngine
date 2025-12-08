/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.hpp
*/

#pragma once

    #include <memory>

    #include <ECS/Registry.hpp>
    #include "plugin/APlugin.hpp"

namespace addon {
namespace eSpec {

class EntitySpec : public te::plugin::APlugin {
 public:
    explicit EntitySpec(ECS::Registry& reg, te::EventManager& events);
};

}  // namespace eSpec
}  // namespace addon

extern "C" {
    std::unique_ptr<addon::eSpec::EntitySpec> get_pfactory(
        ECS::Registry& reg, te::EventManager& events) {
        return std::make_unique<addon::eSpec::EntitySpec>(reg, events);
    }
}
