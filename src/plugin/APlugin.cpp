/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** APlugin.cpp
*/

#include <string>
#include <iostream>

#include "plugin/APlugin.hpp"

namespace te {

APlugin::APlugin(ECS::Registry& reg) : _reg(reg), _components(), _systems() {}

void APlugin::createComponent(const std::string& name,
    const ECS::Entity& e, const json_like& json) {
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


}  // namespace te

