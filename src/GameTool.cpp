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

void GameTool::loadPlugins(std::vector<std::string> &pluginToLoad, const std::string& dir) {
    _pmanager.loadPlugins(_reg, _events, dir, pluginToLoad);
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

std::size_t GameTool::loadMapFile(const std::string& path) {
    _mloader.loadMap(path);
    _maps.push_back(_mloader.getContent());
    return _maps.size() - 1;
}

ECS::Entity GameTool::createMap(std::size_t index, ECS::Entity fentity) {
    if (index >= _maps.size())
        return 0;
    return createEntitiesFromContent(_maps[index], fentity);
}

void GameTool::run(void) {
    while (!_events.isEvent(event::System::Closed)) {
        _events.pollEvents(_reg);
        _events.emit(_reg);
        _reg.runSystems();
    }
}

ECS::Entity GameTool::createEntitiesFromContent(MapLoader::MapContent& content,
    const ECS::Entity& fentity) {
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

