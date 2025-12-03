/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** GameTool.hpp
*/

#pragma once

    #include <string>

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

    void loadPlugins(const std::string& dir = DEFAULT_PLUGIN_RPATH) {
        _pmanager.loadPlugins(_reg, dir);
    }
    void clearPlugins() {
        _pmanager.clear();
    }

    template <typename Component>
    void registerComponent(void) {
        _reg.registerComponent<Component>();
    }

    void createComponent(const std::string& name, const ECS::Entity& e,
        const toml::table& params = {}) {
        _pmanager.loadComponent(name, e, params);
    }
    template <typename Component>
    void createComponent(const ECS::Entity& e, Component&&c) {
        _reg.addComponent(e, c);
    }

    void createSystem(const std::string& name) {
        _pmanager.loadSystem(name);
    }
    void createSystem(const te::sys_builder &f) {
        _reg.addSystem(f);
    }

    void removeEntity(const ECS::Entity& e) {
        _reg.killEntity(e);
    }

    // MAPS
    std::size_t loadMapFile(const std::string& path) {
        _mloader.loadMap(path);
        _maps.push_back(_mloader.getContent());
        return _maps.size();
    }

    ECS::Entity createMap(std::size_t index, ECS::Entity fentity) {
        if (index >= _maps.size())
            return 0;
        return createEntitiesFromContent(_maps[index], fentity);
    }

    void run(void) {
        while (1) {
            _reg.runSystems();
        }
    }

 private:
    ECS::Registry _reg;
    PluginManager _pmanager;

    MapLoader _mloader;
    std::vector<MapLoader::MapContent> _maps;
    ECS::Entity createEntitiesFromContent(MapLoader::MapContent& content,
        const ECS::Entity fentity) {
        ECS::Entity ientity = 0;
        for (std::size_t layer = 0; layer < content.layer_max; ++layer) {
            for (std::size_t y = 0; y < content.map.size(); ++y) {
                for (std::size_t x = 0; x < content.map[y].size(); ++x) {
                    if (layer < content.map[y][x].size()) {
                        toml::table pos;
                        pos.insert("x", static_cast<float>(x * content.tilex));
                        pos.insert("y", static_cast<float>(y * content.tiley));
                        createEntity(fentity + ientity, pos,
                            content.params.at(content.map[y][x][layer]));
                        ientity += 1;
                    }
                }
            }
        }
        return ientity;
    }

    void createEntity(const ECS::Entity& e,
        toml::table& pos, const toml::table& entity_info) {
        for (auto &&[cname, component] : entity_info) {
            if (!std::string(cname.data()).compare("position2")) {
                if (component.is_table()) {
                    const toml::table& compTable = *component.as_table();
                    pos.insert_or_assign("x", pos["x"].value<float>().value() +
                        compTable["x"].value<float>().value());
                    pos.insert_or_assign("y", pos["y"].value<float>().value() +
                        compTable["y"].value<float>().value());
                }
                _pmanager.loadComponent(cname.data(), e, pos);
                continue;
            }
            if (component.is_table()) {
                const toml::table& compTable = *component.as_table();
                _pmanager.loadComponent(cname.data(), e, compTable);
            } else if (component.is_value()) {
                _pmanager.loadComponent(cname.data(), e, {});
            }
        }
    }
};
    
}  // namespace te