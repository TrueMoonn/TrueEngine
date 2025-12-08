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
namespace physic {

class Physic : public te::plugin::APlugin {
 public:
    explicit Physic(ECS::Registry& reg, te::EventManager& events);
};

}  // namespace physic
}  // namespace addon

extern "C" {
    std::unique_ptr<addon::physic::Physic> get_pfactory(ECS::Registry& reg,
        te::EventManager& events) {
        return std::make_unique<addon::physic::Physic>(reg, events);
    }
}
