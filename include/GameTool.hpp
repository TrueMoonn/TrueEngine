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

    #include "config/map_loader.hpp"
    #include "plugin/PluginManager.hpp"

    #define DEFAULT_PLUGIN_RPATH "./plugins/"
    #define SYSTEM_ENTITY 0

namespace te {

class GameTool {
 public:
    GameTool() = default;

    void loadPlugins(const std::string& dir = DEFAULT_PLUGIN_RPATH);
    void clearPlugins();

    template <typename Component>
    void registerComponent(void) {
        _reg.registerComponent<Component>();
    }

    template <typename Component>
    void createComponent(const ECS::Entity& e, Component&&c) {
        _reg.addComponent(e, c);
    }
    void createComponent(const std::string& name, const ECS::Entity& e,
        const toml::table& params = {});

    void createSystem(const std::string& name);
    void createSystem(const te::sys_builder &f);

    void removeEntity(const ECS::Entity& e);

    std::size_t loadMapFile(const std::string& path);
    ECS::Entity createMap(std::size_t index, ECS::Entity fentity);

    void run(void);

 private:
    ECS::Registry _reg;
    PluginManager _pmanager;

    MapLoader _mloader;
    std::vector<MapLoader::MapContent> _maps;
    ECS::Entity createEntitiesFromContent(MapLoader::MapContent& content,
        const ECS::Entity& fentity);
    void createEntity(const ECS::Entity& e,
        toml::table& pos, const toml::table& entity_info);
};

}  // namespace te
