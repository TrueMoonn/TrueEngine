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
    #include "physic/components/velocity.hpp"

namespace addon {
namespace intact {

class Interaction : public te::plugin::APlugin {
 public:
    explicit Interaction(ECS::Registry& reg, te::event::EventManager& events);

 private:
    static void updateVel(const te::event::KeysEvent &event, addon::physic::Velocity2 &vel);
};

}  // namespace intact
}  // namespace addon

extern "C" {
    std::unique_ptr<addon::intact::Interaction> get_pfactory(
        ECS::Registry& reg, te::event::EventManager& events) {
        return std::make_unique<addon::intact::Interaction>(reg, events);
    }
}

