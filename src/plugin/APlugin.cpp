/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** APlugin.cpp
*/

#include <string>
#include <vector>
#include <iostream>
#include <toml++/toml.hpp>

#include "plugin/APlugin.hpp"

namespace te {
namespace plugin {

APlugin::APlugin(ECS::Registry& reg, te::event::EventManager& events) :
    _reg(reg), _events(events), _components(), _systems() {}

void APlugin::createComponent(const std::string& name,
    const ECS::Entity& e, const toml::table& json) {
    if (_components.find(name) != _components.end())
        _components.at(name)(_reg, e, json);
    else
        std::cerr << "error(Plugin): can't find component" << std::endl;
}

void APlugin::createSystem(const std::string& name) {
    if (_systems.find(name) != _systems.end())
        _systems.at(name)(_reg);
    else
        std::cerr << "error(Plugin): can't find system" << std::endl;
}

std::vector<std::string> APlugin::getComponents(void) const {
    std::vector<std::string> names;
    for (auto& [key, _] : _components)
        names.push_back(key);
    return names;
}

std::vector<std::string> APlugin::getSystems(void) const {
    std::vector<std::string> names;
    for (auto& [key, _] : _systems)
        names.push_back(key);
    return names;
}

}  // namespace plugin
}  // namespace te

