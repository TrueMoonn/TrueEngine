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
namespace physic {

class Physic : public te::plugin::APlugin {
 public:
    explicit Physic(ECS::Registry& reg, te::SignalManager& sig);
};

}  // namespace physic
}  // namespace addon

extern "C" {
    #ifdef _WIN32
        __declspec(dllexport)
    #endif
    addon::physic::Physic* get_pfactory(ECS::Registry& reg,
        te::SignalManager& sig) {
        return new addon::physic::Physic(reg, sig);
    }
}
