/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** PluginManager.cpp
*/

#include <vector>
#include <iostream>
#include <string>

#include "plugin/PluginManager.hpp"

namespace te {

PluginManager::PluginManager() : _manager() {}

void PluginManager::loadPlugins(ECS::Registry& reg, const std::string& dir) {
    for (const auto &file : std::filesystem::directory_iterator(dir)) {
        if (!std::filesystem::path(file).extension().compare(".so")) {
            _manager.load(file.path());
            if (_plugins.find(file.path().stem()) == _plugins.end()) {
                try {
                    _plugins[file.path().stem()] =
                        _manager.access<maker>(file.path().stem(),
                        ENDPOINT_NAME)(reg);
                    setAccesser(file.path().stem());
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }
}

std::vector<std::string> PluginManager::getPlugins() const {
    std::vector<std::string> names;

    for (auto& node : _plugins)
        names.push_back(node.first);
    return names;
}

void PluginManager::clear(void) {
    _plugins.clear();
}

void PluginManager::loadComponent(const std::string& name,
    const ECS::Entity& e, const toml::table& params) {
    if (_accesser.find(name) != _accesser.end()) {
        _plugins.at(_accesser.at(name))->createComponent(name, e, params);
    } else  {
        throw PluginManager::NoPluginFound(
            "no plugin found linked to '" + name + "'");
    }
}

void PluginManager::loadSystem(const std::string& name) {
    if (_accesser.find(name) != _accesser.end()) {
        _plugins.at(_accesser.at(name))->createSystem(name);
    } else  {
        throw PluginManager::NoPluginFound(
            "no plugin found linked to '" + name + "'");
    }
}

void PluginManager::setAccesser(const std::string& name) {
    auto cmpts = _plugins.at(name)->getComponents();
    auto syss = _plugins.at(name)->getSystems();

    for (auto cmpt : cmpts)
        _accesser.insert_or_assign(cmpt, name);
    for (auto sys : syss)
        _accesser.insert_or_assign(sys, name);
}

}  // namespace te
