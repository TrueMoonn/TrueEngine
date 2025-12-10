/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** GameTool.hpp
*/

#pragma once

    #include <string>
    #include <vector>

    #include <toml++/toml.hpp>

    #include <ECS/Entity.hpp>
    #include <ECS/Registry.hpp>

    #include "event/EventManager.hpp"
    #include "config/map_loader.hpp"
    #include "plugin/PluginManager.hpp"

    #define DEFAULT_PLUGIN_RPATH "./plugins/"
    #define SYSTEM_ENTITY 0

namespace te {

/**
 * @brief GameTool class for the TrueEngine
 * 
 * This class is a user friendly tool that regroup everything you need to create
 * a game with the TrueEngine.
 * 
 * ```
 * In it you have an instance of:
 *  - ECS::Registry
 *  - te::PluginManager
 *  - te::MapLoader
 * ```
 * 
 */
class GameTool {
 public:
    GameTool() = default;

    /**
     * @brief Load the plugins from the folder given 
     * 
     * @param dir Path to the directory to load plugins
     */
    void loadPlugins(const std::string& dir = DEFAULT_PLUGIN_RPATH);
    /**
     * @brief Clear plugins loaded
     * 
     */
    void clearPlugins(void);

    /**
     * @brief Register a component type in ECS::Registry
     * 
     * @tparam Component The type of the component to register
     */
    template <typename Component>
    void registerComponent(void) {
        _reg.registerComponent<Component>();
    }

    /**
     * @brief Create a component object for the ECS::Entity wanted
     * directly to the registry
     * 
     * @tparam Component The type of the component we register
     * @param e ECS::Entity index to create the component at
     * @param c The rvalued object to register
     */
    template <typename Component>
    void createComponent(const ECS::Entity& e, Component&&c) {
        _reg.addComponent(e, c);
    }
    /**
     * @brief Create a component object for the ECS::Entity wanted
     * through a plugin using the toml++ library for parameters
     * 
     * @param name Name of the component
     * @param e ECS::Entity index to create the component at
     * @param params toml::table with parameters wanted
     */
    void createComponent(const std::string& name, const ECS::Entity& e,
        const toml::table& params = {});

    /**
     * @brief Get a component type in ECS::Registry
     * 
     * @tparam Component The type of the component to get
     */
    template <typename Component>
    void getComponent(void) {
        _reg.getComponent<Component>();
    }

    /**
     * @brief Create a System directly to the ECS::Regitstry
     * 
     * @param f The function to add as system
     */
    void createSystem(const te::plugin::sys_builder &f);
    /**
     * @brief Create a System through a plugin
     * 
     * @param name Name of the system
     */
    void createSystem(const std::string& name);

    /**
     * @brief Remove an ECS::Entity from the ECS::Registry
     * 
     * @param e The ECS::Entity to remove
     */
    void removeEntity(const ECS::Entity& e);

    /**
     * @brief Load a map file 
     * 
     * @param path Path to the file
     * @return The index at wich the MapContent has been stored
     */
    std::size_t loadMapFile(const std::string& path);
    /**
     * @brief Create entities based on MapContent loaded
     * 
     * @param index Witch map to load
     * @param fentity At witch ECS::Entity to start create the map
     * @return Return the last entity used for the map
     */
    ECS::Entity createMap(std::size_t index, ECS::Entity fentity);

    /**
     * @brief Run the main loop
     * 
     * Launch systems in ECS::Registry
     */
    void run(void);

 private:
    plugin::PluginManager _pmanager;
    ECS::Registry _reg;

    MapLoader _mloader;
    std::vector<MapLoader::MapContent> _maps;
    ECS::Entity createEntitiesFromContent(MapLoader::MapContent& content,
        const ECS::Entity& fentity);
    void createEntity(const ECS::Entity& e,
        toml::table& pos, const toml::table& entity_info);

    event::EventManager _events;
};

}  // namespace te
