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

    #define MENU_BEGIN 2
    #define MENU_END (MENU_BEGIN + 10)

namespace addon {
namespace sfml {

class Sfml : public te::plugin::APlugin {
 public:
    explicit Sfml(ECS::Registry& reg, te::SignalManager& events);
};

}  // namespace sfml
}  // namespace addon

extern "C" {
    std::unique_ptr<addon::sfml::Sfml> get_pfactory(ECS::Registry& reg,
        te::SignalManager& events) {
        return std::make_unique<addon::sfml::Sfml>(reg, events);
    }
}
