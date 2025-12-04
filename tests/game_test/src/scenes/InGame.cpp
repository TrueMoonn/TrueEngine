/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** InGame.cpp
*/

#include <plugin/PluginManager.hpp>
#include <config/map_loader.hpp>

#include "scenes/InGame.hpp"

InGame::InGame() : AScene() {
    loadPlugins();
    setECS();
    setEntities();
}

void InGame::setECS(void) {
    createSystem("movement2");
    createSystem("bound_hitbox");
    createSystem("events");
    createSystem("follow_player");
    // createSystem("deal_damage");
    createSystem("draw");
    createSystem("display");
}

void InGame::setEntities(void) {
    createComponent("caca", SYSTEM_ENTITY);
    createComponent("window", SYSTEM_ENTITY);
    createComponent("event_manager", SYSTEM_ENTITY);
    size_t map1_index = loadMapFile(MAPS_PATHS.at("test1"));
    createMap(map1_index, MAP_ENTITY_BACKGROUND);
}
