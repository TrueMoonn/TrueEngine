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
namespace eSpec {

class EntitySpec : public te::plugin::APlugin {
 public:
    explicit EntitySpec(ECS::Registry& reg, te::SignalManager& sig);
};

}  // namespace eSpec
}  // namespace addon

extern "C" {
    #ifdef _WIN32
        __declspec(dllexport)
    #endif
    addon::eSpec::EntitySpec* get_pfactory(
        ECS::Registry& reg, te::SignalManager& sig) {
        return new addon::eSpec::EntitySpec(reg, sig);
    }
}
