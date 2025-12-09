/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** GameTool.cpp
*/

#include <string>
#include <iostream>

#include "GameTool.hpp"

namespace te {

void GameTool::loadPlugins(const std::string& dir) {
    _pmanager.loadPlugins(_reg, _events, dir);
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

std::size_t GameTool::loadFile(ConfigParser::ContentType type,
    const std::string& path) {
    return _configs.parseFile(type, path);
}

ECS::Entity GameTool::createMap(ECS::Entity fentity, std::size_t config,
    std::size_t map) {
    return createEntitiesFromContent(fentity, _configs.getMap(map),
        _configs.getConfig(config));
}

void GameTool::run(void) {
    while (!_events.isEvent(event::System::Closed)) {
        _events.pollEvents(_reg);
        _events.emit(_reg);
        _reg.runSystems();
    }
}

ECS::Entity GameTool::createEntitiesFromContent(const ECS::Entity& fentity,
    ConfigParser::MapContent& map) {
    ECS::Entity ientity = 0;
    for (std::size_t layer = 0; layer < map.layer_max; ++layer) {
        for (std::size_t y = 0; y < map.map.size(); ++y) {
            for (std::size_t x = 0; x < map.map[y].size(); ++x) {
                if (layer < map.map[y][x].size()) {
                    toml::table pos;
                    pos.insert("x", static_cast<float>(x * map.tilex));
                    pos.insert("y", static_cast<float>(y * map.tiley));
                    createEntity(fentity + ientity, pos,
                        map.params.at(map.map[y][x][layer]));
                    ientity += 1;
                }
            }
        }
    }
    return ientity;
}

void GameTool::createEntity(const ECS::Entity& e,
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

}  // namespace te

