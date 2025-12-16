/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** InGame.cpp
*/

#include <ECS/Zipper.hpp>
#include <plugin/PluginManager.hpp>

#include "scenes/InGame.hpp"
#include "map_management.hpp"

#include "clock.hpp"

#include "interaction/components/player.hpp"
#include "physic/components/position.hpp"

InGame::InGame() : AScene() {
    loadPlugins();
    setECS();
    setEntities();
}

void InGame::shootProjectile() {
    static te::Timestamp delay(0.2f);
    static std::size_t entity_proj = PROJ_E;

    if (!isEvent(te::event::KeyPressed) ||
        !getEvents().keys.UniversalKey[/*event map*/te::event::Space] ||
        !delay.checkDelay())
        return;

    const auto &player = getComponent<addon::intact::Player>();
    const auto &position = getComponent<addon::physic::Position2>();

    if (entity_proj > MAX_PROJ_E)
        entity_proj = PROJ_E;
    for (ECS::Entity e = 0; e < player.size() && e < position.size(); ++e) {
        if (player[e].has_value() && position[e].has_value()) {
            createEntity(entity_proj++, "projectile",
                {position[e].value().x + 10, position[e].value().y});
        }
    }
}

void InGame::setECS(void) {
    createSystem("apply_pattern");
    createSystem("movement2");
    createSystem("bound_hitbox");
    createSystem("follow_player");
    createSystem("animate");
    createSystem("deal_damage");
    createSystem("apply_fragile");
    createSystem("kill_entity");
    createSystem("parallax_sys");
    createSystem("draw");
    createSystem("display");
}

void InGame::setEntities(void) {
    createComponent("window", SYSTEM_ENTITY);

    addConfig("assets/configs/base.toml");
    addConfig("assets/configs/enemy.toml");
    addConfig("assets/configs/enemy_2.toml");
    addConfig("assets/configs/player.toml");

    size_t map1 = addMap("assets/maps/test1.ddmap");
    ECS::Entity endMap = createMap(MAP_ENTITY_BACKGROUND, map1);

    createEntity(++endMap, "player", {1920.f / 2, 1080.f / 2});
    createEntity(++endMap, "enemy", {500.f, 500.f});
    createEntity(++endMap, "enemy", {1000.f, 500.f});
    createEntity(++endMap, "enemy", {500.f, 1000.f});
    createEntity(++endMap, "enemy", {600.f, 600.f});
    createEntity(++endMap, "enemy_2", {1000.0f, 500.0f});
    createEntity(++endMap, "enemy_3", {1050.0f, 500.0f});
    createEntity(++endMap, "enemy_4", {1100.0f, 500.0f});
    createEntity(800, "background");
}

void InGame::run(void) {
    while (!isEvent(te::event::System::Closed)) {
        pollEvent();
        shootProjectile();
        emit();
        runSystems();
    }
}
