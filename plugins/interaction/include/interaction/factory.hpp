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
namespace intact {

class Interaction : public te::plugin::APlugin {
 public:
    explicit Interaction(ECS::Registry& reg, te::SignalManager& sig);
};

}  // namespace intact
}  // namespace addon

extern "C" {
    addon::intact::Interaction* get_pfactory(
        ECS::Registry& reg, te::SignalManager& sig) {
        return new addon::intact::Interaction(reg, sig);
    }
}
