/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** InGame.cpp
*/

#include <plugin/PluginManager.hpp>

#include "scenes/in_game/InGame.hpp"

#include "scenes/in_game/in_game.cpmt.hpp"
#include "scenes/in_game/in_game.sys.hpp"
#include "components/clock.hpp"

InGame::InGame() : AScene() {
    te::PluginManager::loadPlugins(_reg);
    setECS();
    setEntities();
}

void InGame::setECS(void) {
    _reg.registerComponent<te::Window>();

    te::PluginManager::loadSystem("movement", "movement2");
    te::PluginManager::loadSystem("physic", "bound_hitbox");
    _reg.addSystem(&te::manageEvent);
    te::PluginManager::loadSystem("display", "follow_player");
    te::PluginManager::loadSystem("display", "draw");
    te::PluginManager::loadSystem("display", "display");
}

void InGame::setEntities(void) {
    _reg.addComponent(MAIN_WINDOW, te::Window());
    load_map(_reg, MAPS_PATHS.at("test1"));
}

void InGame::run(void) {
    struct te::Clock clock(CLOCK_RATE);

    while (MAIN_WIN_EXIST && MAIN_WIN_ISOPEN) {
        if (clock.checkCooldown()) {
            _reg.runSystems();
        }
    }
}
