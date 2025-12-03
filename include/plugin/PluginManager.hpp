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
    #include <vector>
    #include <toml++/toml.hpp>

    #include "plugin/DlManager.hpp"
    #include "plugin/APlugin.hpp"

    #define ENDPOINT_NAME "get_pfactory"

namespace te {

class PluginManager {
    typedef std::unique_ptr<APlugin>(*maker)(ECS::Registry&);

 public:
<<<<<<< Updated upstream
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
                        setAccesser(file.path().stem());
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

    static void loadComponent(const std::string& name,
        const ECS::Entity& e, const toml::table& params = {}) {
        if (_accesser.find(name) != _accesser.end()) {
            _plugins.at(_accesser.at(name))->createComponent(name, e, params);
        } else  {
            std::cerr << "error(Plugin): not plugin " << \
                "found linked to '" << name << "'" << std::endl;
        }
    }

    static void loadSystem(const std::string& name) {
        if (_accesser.find(name) != _accesser.end()) {
            _plugins.at(_accesser.at(name))->createSystem(name);
        } else  {
            std::cerr << "error(Plugin): not plugin " << \
                "found linked to '" << name << "'" << std::endl;
        }
    }
=======
    PluginManager();
    ~PluginManager() = default;

    void loadPlugins(ECS::Registry& reg, const std::string& dir);
    std::vector<std::string> getPlugins() const;
    void clear(void);
    void loadComponent(const std::string& name,
        const ECS::Entity& e, const toml::table& params);
    void loadSystem(const std::string& name);
>>>>>>> Stashed changes

 private:
    void setAccesser(const std::string& name);
    std::unordered_map<std::string, std::string> _accesser;

    DlManager _manager;
    std::unordered_map<std::string,
        std::unique_ptr<APlugin>> _plugins;
};

}  // namespace te
