/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** GameTool.cpp
*/

#include <string>
#include <iostream>
#include <toml++/toml.hpp>

#include "GameTool.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Registry.hpp"

namespace te {

void GameTool::loadPlugins(const std::string& dir) {
    _pmanager.loadPlugins(_reg, _signals, dir);
}

void GameTool::clearPlugins() {
    _pmanager.clear();
}

void GameTool::createComponent(const std::string& name, const ECS::Entity& e,
    const toml::table& params) {
    try {
        _pmanager.loadComponent(name, e, params);
    } catch (const plugin::PluginManager::NoPluginFound& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameTool::createSystem(const std::string& name) {
    try {
        _pmanager.loadSystem(name);
    } catch (const plugin::PluginManager::NoPluginFound& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameTool::createSystem(const te::plugin::sys_builder &f) {
    _reg.addSystem(f);
}

void GameTool::removeEntity(const ECS::Entity& e) {
    _reg.killEntity(e);
}

const ECS::Registry& GameTool::getRegistry(void) const {
    return _reg;
}

std::size_t GameTool::addMap(const std::string& path) {
    return _configs.addMap(path);
}

void GameTool::addConfig(const std::string& path) {
    _configs.addConfig(path);
}

void GameTool::createEntity(ECS::Entity e, const std::string& name,
    const mat::Vector2f& pos) {
    DEBUG_GT("GameTool: Creating Entity: creating entity ({})\n\
\tCalled '{}' at position x={} and y ={}", e, name, pos.x, pos.y);
    toml::table entityConfig = _configs.getEntityConfig(name);
    createEntityComponents(e, entityConfig, pos);
}

ECS::Entity GameTool::createMap(ECS::Entity fentity, std::size_t mapIndex) {
    DEBUG_GT("GameTool: Creating Map: creating a map {}...", mapIndex);
    ECS::Entity ientity = 0;
    const ConfigParser::MapContent map = _configs.getMap(mapIndex);
    mat::Vector2f tileSize = getMapTileSize(
        _configs.getEntityConfig(CONFIG_MAP_TABLE_NAME).as_table());
    for (std::size_t y = 0; y < map.map.size(); ++y) {
        for (std::size_t x = 0; x < map.map[y].size(); ++x) {
            for (std::size_t e = 0; e < map.map[y][x].size(); ++e) {
                DEBUG_GT("GameTool: Creating Map: creating entity ({})\n\
\tCalled '{}' at position x={} and y={}",
                    fentity + ientity, map.map[y][x][e],
                    tileSize.x * x, tileSize.y * y);
                createEntityComponents(fentity + ientity,
                    _configs.getEntityConfig(map.map[y][x][e]),
                    mat::Vector2f{tileSize.x * x, tileSize.y * y});
                ientity += 1;
            }
        }
    }
    return ientity + fentity;
}

void GameTool::runSystems() {
    _reg.runSystems();
}

mat::Vector2f GameTool::getMapTileSize(const toml::table *table) {
    mat::Vector2f tileSize(CONFIG_MAP_TILE_DEFAULT_SIZE,
        CONFIG_MAP_TILE_DEFAULT_SIZE);
    if (table != nullptr) {
        tileSize.x = (*table)["x"].value_or(CONFIG_MAP_TILE_DEFAULT_SIZE);
        tileSize.y = (*table)["y"].value_or(CONFIG_MAP_TILE_DEFAULT_SIZE);
    }
    return tileSize;
}

void GameTool::createEntityComponents(const ECS::Entity& e,
    toml::table conf, const mat::Vector2f& pos) {
    if (conf["position2"].is_table()) {
        toml::table nPos;
        const toml::table* position = conf["position2"].as_table();
        nPos.insert_or_assign("x", (*position)["x"].value_or(0.f) + pos.x);
        nPos.insert_or_assign("y", (*position)["y"].value_or(0.f) + pos.y);
        conf.insert_or_assign("position2", nPos);
    } else if (conf["position2"].is_value()) {
        toml::table nPos;
        nPos.insert_or_assign("x", pos.x);
        nPos.insert_or_assign("y", pos.y);
        conf.insert_or_assign("position2", nPos);
    }
    for (auto &&[cname, component] : conf) {
        DEBUG_GT("\t\tAdding component {}", cname.data());
        if (component.is_table()) {
            const toml::table& compTable = *component.as_table();
            if (_local_components.find(cname.data())
                != _local_components.end()) {
                _local_components.at(cname.data())(e, compTable);
            } else {
                _pmanager.loadComponent(cname.data(), e, compTable);
            }
        } else if (component.is_value()) {
            if (_local_components.find(cname.data())
                != _local_components.end()) {
                _local_components.at(cname.data())(e, {});
            } else {
                _pmanager.loadComponent(cname.data(), e, {});
            }
        }
    }
    DEBUG_GT("\tCreation DONE");
}

}  // namespace te
