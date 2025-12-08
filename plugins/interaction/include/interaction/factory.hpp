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
namespace intact {

class Interaction : public te::plugin::APlugin {
 public:
    explicit Interaction(ECS::Registry& reg, te::EventManager& events);
};

}  // namespace intact
}  // namespace addon

extern "C" {
    std::unique_ptr<addon::intact::Interaction> get_pfactory(
        ECS::Registry& reg, te::EventManager& events) {
        return std::make_unique<addon::intact::Interaction>(reg, events);
    }
}

