/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** GameTool.hpp
*/

#pragma once

    #include <functional>
    #include <string>
    #include <unordered_map>
    #include <utility>
    #include <toml++/toml.hpp>

    #include <ECS/Entity.hpp>
    #include <ECS/Registry.hpp>
    #include <ECS/DenseSA.hpp>

    #include "Scene.hpp"
    #include "maths/Vector.hpp"
    #include "SignalManager.hpp"
    #include "ConfigReader.hpp"
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
    typedef std::function<void(ECS::Entity, const toml::table&)>
        local_cmt_build;

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

    template <typename Component>
    void registerComponent(const std::string& name,
        const local_cmt_build& func) {
        _reg.registerComponent<Component>();
        _local_components.insert_or_assign(name, func);
    }

    /**
     * @brief Create a component object for the ECS::Entity wanted
     * directly to the registry
     *
     * @tparam Component The type of the component we register
     * @param e ECS::Entity index to create the component at
     * @param c The rvalued object to register
     */
     template <typename Component, typename... Args>
     void createComponent(const ECS::Entity& e, Args&&... args) {
         _reg.createComponent<Component>(e, std::forward<Args>(args)...);
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
    ECS::DenseSparseArray<Component>& getComponent(void) {
        return _reg.getComponents<Component>();
    }

    /**
     * @brief Create a System directly to the ECS::Regitstry
     *
     * @param name The name of the system
     * @param f The function to add as system
     */
    void createSystem(const std::string& name,
        const te::plugin::sys_builder &f);
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
     * @brief Load a map into the ConfigParser
     *
     * @param path Filepath to the map to load
     * @return `std::size_t` The index in wich the map is stored
     */
    std::size_t addMap(const std::string& path);

    /**
     * @brief Load a configuration file into the ConfigParser
     *
     * @param path Filepath to the configuration file
     */
    void addConfig(const std::string& path);

    /**
     * @brief Create an Entity into the ECS::Registry based on the
     * configurations loaded before into the ConfigParser
     *
     * @param e ECS::Entity to load the components to
     * @param name Name of the entity in the configuration
     * @param pos Position to gave to the entity - Default {0, 0}
     */
    void createEntity(ECS::Entity e, const std::string& name,
        const mat::Vector2f& pos = {0, 0});

    /**
     * @brief Create every ECS::Entity based on the map at the index given
     * and the configurations given for every entities
     *
     * @param index Index of the map stored in ConfigParser
     * @param fentity Index of where to start the map loading in the
     * ECS::Registry
     * @return `ECS::Entity` The last entity used for the map
     */
    ECS::Entity createMap(std::size_t index, ECS::Entity fentity);

    /**
     * @brief Poll events done by the user
     *
     */
    void pollEvent();

    /**
     * @brief Run all systems registered in the registry
     *
     */
    void runSystems();

    /**
     * @brief Get the ECS::Registry stored in this class
     *
     * @return A copy of the ECS::Registry
     */
    const ECS::Registry& getRegistry(void) const;

    template<typename... Args, typename Func>
    void sub(const std::string& name, Func&& func) {
        _signals.sub<Args...>(name, func);
    }

    template<typename... Args>
    void emit(const std::string& name, Args&&... args) {
        _signals.emit(name, std::forward<Args>(args)...);
    }

    std::size_t addScene(const Scene& scene) {
        _scenes.push_back(scene);
        return _scenes.size() - 1;
    }

    void switchScene(std::size_t idx, bool clear = false) {
        if (idx >= _scenes.size())
            return;
        for (std::size_t i = 0; clear && i < _scenes.size(); ++i) {
            if (_scenes[i].active && i != idx)
                clearScene(i);
        }
        if (!isSceneActive(idx)) {
            for (auto& sys : _scenes[idx].systems) {
                if (_sysMap.find(sys) == _sysMap.end()) {
                    _sysMap[sys] = {};
                }
                _sysMap.at(sys).push_back(idx);
                createSystem(sys);
            }

            for (auto& e : _scenes[idx].entities) {
                createEntity(e.idx, e.name, e.pos);
            }
            _scenes[idx].active = true;
        }
    }

    void clearScene(std::size_t idx) {
        if (idx < _scenes.size() && isSceneActive(idx)) {
            _scenes[idx].active = false;
            for (auto& e : _scenes[idx].entities)
                _reg.killEntity(e.idx);
            for (auto& sys : _scenes[idx].systems) {
                if (_sysMap.size() <= 0) {
                    _reg.removeSystem(sys);
                }
            }
        }
    }

    void deleteScene(std::size_t idx) {
        if (idx < _scenes.size()) {
            clearScene(idx);
            _scenes.erase(_scenes.begin() + idx);
        }
    }

    bool isSceneActive(std::size_t idx) const {
        if (idx < _scenes.size()) {
            return _scenes[idx].active;
        }
        return false;
    }

 private:
    plugin::PluginManager _pmanager;
    ECS::Registry _reg;

    ConfigParser _configs;
    std::unordered_map<std::string, local_cmt_build> _local_components;
    mat::Vector2f getMapTileSize(const toml::table *table);
    void createEntityComponents(const ECS::Entity& e, toml::table conf,
        const mat::Vector2f& pos);

    SignalManager _signals;

    std::vector<Scene> _scenes;
    std::unordered_map<std::string, std::vector<std::size_t>> _sysMap;
    std::unordered_map<std::string, std::vector<std::size_t>> _sigMapoy;
};

}  // namespace te
