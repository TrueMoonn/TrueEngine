/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** InGame.cpp
*/

#include <plugin/PluginManager.hpp>
#include <config/map_loader.hpp>

#include "clock.hpp"
#include "window.hpp"
#include "event.hpp"

#include "scenes/InGame.hpp"

InGame::InGame() : AScene() {
    te::PluginManager::loadPlugins(_reg);
    setECS();
    setEntities();
}

void InGame::setECS(void) {
    _reg.registerComponent<te::Window>();

    te::PluginManager::loadSystem("movement2");
    te::PluginManager::loadSystem("bound_hitbox");
    _reg.addSystem(&te::manageEvent);
    te::PluginManager::loadSystem("follow_player");
    te::PluginManager::loadSystem("animate");
    te::PluginManager::loadSystem("draw");
    te::PluginManager::loadSystem("display");
}

void InGame::setEntities(void) {
    te::MapLoader loader(MAP_ENTITY_BACKGROUND, MAP_MAX_ENTITY_BACKGROUND);
    _reg.addComponent(MAIN_WINDOW, te::Window());
    loader.loadMap(MAPS_PATHS.at("test1"));
}

void InGame::run(void) {
    struct te::Timestamp clock(SEC_TO_MICRO(1.0 / 60));

    while (MAIN_WIN_EXIST && MAIN_WIN_ISOPEN) {
        if (clock.checkDelay()) {
            _reg.runSystems();
        }
    }
}
