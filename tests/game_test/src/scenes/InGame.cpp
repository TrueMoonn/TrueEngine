/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** InGame.cpp
*/

#include <plugin/PluginManager.hpp>

#include "scenes/InGame.hpp"

InGame::InGame() : AScene() {
    loadPlugins();
    setECS();
    setEntities();
}

void InGame::setECS(void) {
    createSystem("movement2");
    createSystem("bound_hitbox");
    createSystem("follow_player");
    createSystem("animate");
    createSystem("deal_damage");
    createSystem("kill_entity");
    createSystem("draw");
    createSystem("display");
}

void InGame::setEntities(void) {
    createComponent("window", SYSTEM_ENTITY);

    addConfig("assets/configs/base.toml");
    addConfig("assets/configs/enemy.toml");

    size_t map1 = addMap("assets/maps/test1.ddmap");
    ECS::Entity endMap = createMap(MAP_ENTITY_BACKGROUND, map1);

    createEntity(endMap + 1, "enemy", {500.f, 500.f});
}
