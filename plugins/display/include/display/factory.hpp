/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** factory.hpp
*/

#pragma once

    #include <memory>

    #include <ECS/Registry.hpp>
    #include <SignalManager.hpp>

    #include <plugin/APlugin.hpp>

namespace addon {
namespace display {

class Display : public te::plugin::APlugin {
 public:
    explicit Display(ECS::Registry& reg, te::SignalManager& sig);
};

}  // namespace display
}  // namespace addon

extern "C" {
    addon::display::Display* get_pfactory(
        ECS::Registry& reg, te::SignalManager& sig) {
        return new addon::display::Display(reg, sig);
    }
}
