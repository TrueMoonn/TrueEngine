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

/**
 * @brief Plugin Manager class for TrueEngine
 * 
 * This class load use DlManager class to load dynamic libraries and get
 * `std::unique_ptr<te::APlugin>(*)(ECS::Registry&)` symbol from an endpoint
 * 
 * Then the te::APlugin is used as a factory and will create components or
 * systems for the ECS::Registry associated with names  
 * 
 */
class PluginManager {
    typedef std::unique_ptr<APlugin>(*maker)(ECS::Registry&);

 public:
    TE_EXCEPTION("PluginManager", NoPluginFound)

 public:
    PluginManager();
    ~PluginManager() = default;

    /**
     * @brief Load TrueEngine plugins
     * 
     * This function load plugins he found in the directory and store
     * the factory (te::APlugin) he found
     * 
     * @param reg The ECS::Registry to load to
     * @param dir The path to the plugins
     */
    void loadPlugins(ECS::Registry& reg, const std::string& dir);
    /**
     * @brief Get the names of the plugins loaded
     * 
     * @return a std::vector<std::string> of every plugin names
     */
    std::vector<std::string> getPlugins() const;
    /**
     * @brief Clear the actual plugins loaded
     * 
     */
    void clear(void);

    /**
     * @brief Load a component with factory to the ECS::Registry she is
     * linked to based on the name
     * 
     * @param name Name of the component to load
     * @param e The ECS::Entity to link the component to
     * @param params toml::table parameter to create the component with
     */
    void loadComponent(const std::string& name,
        const ECS::Entity& e, const toml::table& params);
    /**
     * @brief Load a system to the ECS::Registry with the factory linked to
     * based on the name
     * 
     * @param name Name of the system to load
     */
    void loadSystem(const std::string& name);

 private:
    /**
     * @brief Set simpler access
     * 
     * This function is used to create a link between objects of the plugin
     * and the actual plugin to simplify the access later
     * 
     * @param name Name of the plugin
     */
    void setAccesser(const std::string& name);
    std::unordered_map<std::string, std::string> _accesser;

    DlManager _manager;
    std::unordered_map<std::string,
        std::unique_ptr<APlugin>> _plugins;
};

}  // namespace te
