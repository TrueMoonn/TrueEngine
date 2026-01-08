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
#include "SignalManager.hpp"

namespace te {
namespace plugin {

void PluginManager::loadPlugins(ECS::Registry& reg,
    SignalManager& sig, const std::string& dir) {
    DPLUGIN("PluginManager: Loading plugins: from directory '{}'", dir);
    for (const auto &file : std::filesystem::directory_iterator(dir)) {
        if (file.path().extension() == ".so") {
            std::string pname = file.path().stem().string();
            DPLUGIN("PluginManager: Loading plugins: loading '{}'", pname);
            _manager.load(file.path());
            try {
                DPLUGIN("PluginManager: Loading plugins: loading '{}'", pname);
                maker plugin = _manager.access<maker>(pname, ENDPOINT_NAME);
                _plugins[pname] = plugin(reg, sig);
                setAccesser(pname);
            } catch (const std::runtime_error& e) {
                DPLUGIN("PluginManager: Loading plugins: symbol not found");
            }
        }
    }
}

void PluginManager::loadPlugins(ECS::Registry& reg,
    SignalManager& sig, const std::string& dir,
    std::vector<std::string> &pluginToLoad) {
    DPLUGIN("PluginManager: Loading plugins: from directory '{}'", dir);
    for (const auto &file : std::filesystem::directory_iterator(dir)) {
        if (file.path().extension() == ".so") {
            std::string pname = file.path().stem().string();
            DPLUGIN("PluginManager: Loading plugins: loading '{}'", pname);
            for (auto &plugin : pluginToLoad) {
                if (plugin.compare(pname) == 0) {
                    std::cout << plugin << std::endl;
                    _manager.load(file.path());
                    try {
                        DPLUGIN("PluginManager: Loading plugins:\
loading '{}'", pname);
                        maker plugin = _manager.access<maker>(pname,
                            ENDPOINT_NAME);
                        _plugins[pname] = plugin(reg, sig);
                        setAccesser(pname);
                    } catch (const std::runtime_error& e) {
                        DPLUGIN("PluginManager: Loading plugins:\
symbol not found");
                    }
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
    _accesser.clear();
    _plugins.clear();
}

void PluginManager::loadComponent(const std::string& name,
    const ECS::Entity& e, const toml::table& params) {
    DPLUGIN("PluginManager: Loading Component:\
loading component '{}' at entity {}", name, e);
    if (_accesser.find(name) != _accesser.end()) {
        _plugins.at(_accesser.at(name))->createComponent(name, e, params);
        DPLUGIN("PluginManager: Loading Component: component loaded OK");
    } else  {
        throw PluginManager::NoPluginFound(
            "no plugin found linked to '" + name + "'");
    }
}

void PluginManager::loadSystem(const std::string& name) {
    DPLUGIN("PluginManager: Loading System: called '{}'", name);
    if (_accesser.find(name) != _accesser.end()) {
        _plugins.at(_accesser.at(name))->createSystem(name);
        DPLUGIN("PluginManager: Loading System: system loaded OK");
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

}  // namespace plugin
}  // namespace te
