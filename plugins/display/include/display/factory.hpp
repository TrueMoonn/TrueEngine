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
namespace display {

class Display : public te::plugin::APlugin {
 public:
    explicit Display(ECS::Registry& reg, te::EventManager& events);
};

}  // namespace display
}  // namespace addon

extern "C" {
    std::unique_ptr<addon::display::Display> get_pfactory(
        ECS::Registry& reg, te::EventManager& events) {
        return std::make_unique<addon::display::Display>(reg, events);
    }
}
