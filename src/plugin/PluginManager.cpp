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

void PluginManager::loadPlugins(ECS::Registry& reg, const std::string& dir) {
    for (const auto &file : std::filesystem::directory_iterator(dir)) {
        if (file.path().extension() == ".so") {
            std::string pname = file.path().stem().string();
            _manager.load(file.path());
            try {
                _pollEvent = _manager.access<EventManager::pollFunc>(
                    pname, POLL_EVENT_ENDPOINT);
                _isPollEvent = true;
            } catch (const std::runtime_error&) {}
            try {
                maker plugin = _manager.access<maker>(pname, ENDPOINT_NAME);
                _plugins[pname] = plugin(reg);
                setAccesser(pname);
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
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
    _accesser.clear();
    _plugins.clear();
    _manager.closeHandlers();
    _pollEvent = {};
    _isPollEvent = false;
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

    for (const auto& cmpt : cmpts)
        _accesser.insert_or_assign(cmpt, name);
    for (const auto& sys : syss)
        _accesser.insert_or_assign(sys, name);
}

}  // namespace te
