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
    _reg.registerComponent<te::Movable>();
    _reg.registerComponent<te::Player>();
    _reg.registerComponent<te::Hitbox>();
    _reg.registerComponent<te::Interactive>();
    _reg.registerComponent<te::Window>();

    te::PluginManager::loadSystem("movement", "movement2");
    _reg.addSystem(&te::hitbox2_sys);
    _reg.addSystem(&te::player_interaction_sys);
    _reg.addSystem(&te::manageEvent);
    te::PluginManager::loadSystem("window", "follow_player");
    te::PluginManager::loadSystem("window", "draw");
    te::PluginManager::loadSystem("window", "display");
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
