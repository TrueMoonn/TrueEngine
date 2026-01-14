/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** GameTool.cpp
*/

#include <string>
#include <iostream>
#include <toml++/toml.hpp>

#include <ECS/Entity.hpp>
#include <ECS/Registry.hpp>

#include "GameTool.hpp"

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

void GameTool::createSystem(const std::string& name,
    const te::plugin::sys_builder &f, bool to_load) {
    _systems.insert_or_assign(name, f);
    if (to_load) {
        if (_reg.getSystem(name) != -1)
            return;
        _reg.addSystem(name, f);
    }
}

void GameTool::createSystem(const std::string& name) {
    if (_reg.getSystem(name) != -1)
        return;
    if (_systems.find(name) != _systems.end()) {
        _reg.addSystem(name, _systems.at(name));
        return;
    }
    try {
        _pmanager.loadSystem(name);
    } catch (const plugin::PluginManager::NoPluginFound& e) {
        std::cerr << e.what() << std::endl;
    }
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
    toml::table entityConfig = _configs.getEntityConfig(name);
    createEntityComponents(e, entityConfig, pos);
}

ECS::Entity GameTool::createMap(ECS::Entity fentity, std::size_t mapIndex) {
    ECS::Entity ientity = 0;
    const ConfigParser::MapContent map = _configs.getMap(mapIndex);
    mat::Vector2f tileSize = getMapTileSize(
        _configs.getEntityConfig(CONFIG_MAP_TABLE_NAME).as_table());
    for (std::size_t y = 0; y < map.map.size(); ++y) {
        for (std::size_t x = 0; x < map.map[y].size(); ++x) {
            for (std::size_t e = 0; e < map.map[y][x].size(); ++e) {
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
    processSceneQueue();
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
}

void GameTool::enableSceneCallbacks(std::size_t idx) {
    if (idx < _scenes.size()) {
        for (auto callback_id : _scenes[idx].signal_callbacks) {
            _signals.enableCallback(callback_id);
        }
    }
}

void GameTool::disableSceneCallbacks(std::size_t idx) {
    if (idx < _scenes.size()) {
        for (auto callback_id : _scenes[idx].signal_callbacks) {
            _signals.disableCallback(callback_id);
        }
    }
}

void GameTool::updateScene(te::sStatus act, std::size_t idx) {
    _scene_action_queue.push_back({act, idx});
}

void GameTool::processSceneQueue() {
    for (const auto& scene : _scene_action_queue) {
        switch (scene.action) {
            case te::sStatus::ACTIVATE:
                activateScene(scene.idx);
                break;
            case te::sStatus::DEACTIVATE:
                deactivateScene(scene.idx);
                break;
            case te::sStatus::PAUSE:
                pauseScene(scene.idx);
                break;
            case te::sStatus::RESUME:
                resumeScene(scene.idx);
                break;
        }
    }
    _scene_action_queue.clear();
}

std::size_t GameTool::addScene(const Scene& scene) {
    Scene new_scene = scene;
    new_scene.state = Scene::SceneState::INACTIVE;
    _scenes.push_back(new_scene);
    return _scenes.size() - 1;
}

void GameTool::activateScene(std::size_t idx) {
    if (idx >= _scenes.size() ||
        _scenes[idx].state == Scene::SceneState::ACTIVE)
        return;

    _scenes[idx].state = Scene::SceneState::ACTIVE;
    if (_scenes[idx].on_activate)
        _scenes[idx].on_activate();
    enableSceneCallbacks(idx);
    createSceneEntities(idx);
    rebuildSystems();
}

void GameTool::deactivateScene(std::size_t idx) {
    if (idx >= _scenes.size() ||
        _scenes[idx].state == Scene::SceneState::INACTIVE)
        return;

    Scene& scene = _scenes[idx];
    scene.state = Scene::SceneState::INACTIVE;
    disableSceneCallbacks(idx);
    destroySceneEntities(idx);
    rebuildSystems();
}

void GameTool::pauseScene(std::size_t idx) {
    if (idx >= _scenes.size() ||
        _scenes[idx].state != Scene::SceneState::ACTIVE)
        return;

    Scene& scene = _scenes[idx];
    scene.state = Scene::SceneState::PAUSED;
    disableSceneCallbacks(idx);
    rebuildSystems();
}

void GameTool::resumeScene(std::size_t idx) {
    if (idx >= _scenes.size() ||
        _scenes[idx].state != Scene::SceneState::PAUSED)
        return;

    Scene& scene = _scenes[idx];
    scene.state = Scene::SceneState::ACTIVE;
    enableSceneCallbacks(idx);
    rebuildSystems();
}

void GameTool::deactivateAllScenes() {
    for (std::size_t i = 0; i < _scenes.size(); ++i) {
        if (_scenes[i].state != Scene::SceneState::INACTIVE) {
            _scenes[i].state = Scene::SceneState::INACTIVE;
            deactivateScene(i);
        }
    }
    rebuildSystems();
}

void GameTool::rebuildSystems() {
    _reg.clearSystems();

    std::array<std::vector<std::string>,
        Scene::PHASES::PHASE_MAX> uniq_sys;
    for (const auto& scene : _scenes) {
        if (scene.state == Scene::SceneState::ACTIVE) {
            for (std::size_t phase = 0; phase <
                Scene::PHASES::PHASE_MAX; ++phase) {
                for (const auto& sys_name : scene.systems[phase]) {
                    if (std::find(uniq_sys[phase].begin(),
                        uniq_sys[phase].end(), sys_name) ==
                        uniq_sys[phase].end())
                        uniq_sys[phase].push_back(sys_name);
                }
            }
        }
    }

    for (std::size_t phase = 0; phase < Scene::PHASES::PHASE_MAX; ++phase) {
        for (const auto& sys_name : uniq_sys[phase]) {
            createSystem(sys_name);
        }
    }
}

void GameTool::createSceneEntities(std::size_t idx) {
    if (idx < _scenes.size()) {
        for (auto& e : _scenes[idx].entities) {
            createEntity(e.idx, e.name, e.pos);
        }
    }
}

void GameTool::destroySceneEntities(std::size_t idx) {
    if (idx < _scenes.size()) {
        for (auto& e : _scenes[idx].entities) {
            removeEntity(e.idx);
        }
    }
}

}  // namespace te
