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

    #include "Exception.hpp"
    #include "plugin/DlManager.hpp"
    #include "plugin/APlugin.hpp"

    #define ENDPOINT_NAME "get_pfactory"

namespace te {

class PluginManager {
    typedef std::unique_ptr<APlugin>(*maker)(ECS::Registry&);
 public:
    TE_EXCEPTION("PluginManager", NoPluginFound)

 public:
    PluginManager();
    ~PluginManager() = default;

    void loadPlugins(ECS::Registry& reg, const std::string& dir);
    std::vector<std::string> getPlugins() const;
    void clear(void);
    void loadComponent(const std::string& name,
        const ECS::Entity& e, const toml::table& params);
    void loadSystem(const std::string& name);

 private:
    void setAccesser(const std::string& name);
    std::unordered_map<std::string, std::string> _accesser;

    DlManager _manager;
    std::unordered_map<std::string,
        std::unique_ptr<APlugin>> _plugins;
};

}  // namespace te
