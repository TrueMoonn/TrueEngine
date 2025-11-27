/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** PluginManager.hpp
*/

#pragma once

    #include <memory>
    #include <filesystem>
    #include <functional>
    #include <iostream>
    #include <string>
    #include <unordered_map>

    #include "plugin/DlManager.hpp"
    #include "plugin/APlugin.hpp"

    #define ENDPOINT_NAME "get_pfactory"
    #define DEFAULT_PLUGIN_RPATH "./plugins/"

namespace te {

class PluginManager {
    typedef std::unique_ptr<APlugin>(*maker)(ECS::Registry&);

 public:
    PluginManager() = delete;
    ~PluginManager() {
        clear();
    }

    static void loadPlugins(ECS::Registry& reg,
        const std::string& directory = DEFAULT_PLUGIN_RPATH) {
        clear();
        for (const auto &file :
            std::filesystem::directory_iterator(directory)) {
            if (!std::filesystem::path(file).extension().compare(".so")) {
                _manager.load(file.path());
                if (_plugins.find(file.path().stem()) == _plugins.end()) {
                    try {
                        _plugins[file.path().stem()] =
                            _manager.access<maker>(file.path().stem(),
                            ENDPOINT_NAME)(reg);
                    } catch (const std::runtime_error& e) {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
        }
    }

    static std::vector<std::string> getPlugins() {
        std::vector<std::string> names(_plugins.size());

        for (auto& node : _plugins)
            names.push_back(node.first);
        return names;
    }

    static void clear(void) {
        _manager.closeHandlers();
        _plugins.clear();
    }

    static void loadComponent(const std::string& plugin,
        const std::string& name, const ECS::Entity& e,
        const json_like& json = {}) {
        if (_plugins.find(plugin) != _plugins.end()) {
            _plugins.at(plugin)->createComponent(name, e, json);
        }
    }

    static void loadSystem(const std::string& plugin,
            const std::string& name) {
        if (_plugins.find(plugin) != _plugins.end()) {
            _plugins.at(plugin)->createSystem(name);
        }
    }

 private:
    static inline DlManager _manager;
    static inline std::unordered_map<std::string,
        std::unique_ptr<APlugin>> _plugins;
};

}  // namespace te
