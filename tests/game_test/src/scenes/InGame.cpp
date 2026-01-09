/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** InGame.cpp
*/
#include <iostream>

#include <ECS/DenseZipper.hpp>
#include <plugin/PluginManager.hpp>

#include "scenes/InGame.hpp"
#include "ECS/Entity.hpp"
#include "map_management.hpp"
#include "events.hpp"

#include "clock.hpp"

#include "interaction/components/player.hpp"
#include "physic/components/position.hpp"
#include "physic/components/velocity.hpp"

InGame::InGame() : AScene() {
    loadPlugins();
    setECS();
    setEntities();
}

void InGame::setECS(void) {
    createSystem("poll_event");
    createSystem("apply_pattern");
    createSystem("movement2");
    createSystem("bound_hitbox");
    createSystem("follow_player");
    createSystem("animate");
    createSystem("deal_damage");
    createSystem("apply_fragile");
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

    std::size_t map1 = addMap("assets/maps/test1.ddmap");
    ECS::Entity endMap = createMap(MAP_ENTITY_BACKGROUND, map1);

    createEntity(++endMap, "player", {1920.f / 2, 1080.f / 2});
    createEntity(++endMap, "enemy", {500.f, 500.f});
    createEntity(++endMap, "enemy", {1000.f, 500.f});
    createEntity(++endMap, "enemy", {500.f, 1000.f});
    createEntity(++endMap, "enemy", {600.f, 600.f});
    createEntity(++endMap, "enemy", {1000.0f, 500.0f});
    createEntity(++endMap, "enemy", {1050.0f, 500.0f});
    createEntity(++endMap, "enemy", {1100.0f, 500.0f});
    createEntity(800, "background");
}

void InGame::run(void) {
    sub("closed", [this](){this->state = GameState::CLOSED;});
    sub<ECS::Entity>("no_health_entity", [this](ECS::Entity e){
        removeEntity(e);
    });
    sub<ECS::Entity>("broken_entity", [this](ECS::Entity e){
        removeEntity(e);
    });
    sub<ECS::Entity>("timout_entity", [this](ECS::Entity e){
        removeEntity(e);
    });
    sub<te::Keys>("key_input", [this](te::Keys keys){
        auto& players = this->getComponent<addon::intact::Player>();
        auto& velocities = this->getComponent<addon::physic::Velocity2>();

        for (auto &&[_, vel] : ECS::DenseZipper(players, velocities)) {
            if (keys[te::Key::Z]) {
                vel.y = -170.0;
            } else if (keys[te::Key::S]) {
                vel.y = 170.0;
            } else {
                vel.y = 0.0;
            }
            if (keys[te::Key::Q]) {
                vel.x = -170.0;
            } else if (keys[te::Key::D]) {
                vel.x = 170.0;
            } else {
                vel.x = 0.0;
            }
        }
    });
    sub<te::Keys>("key_input", [this](te::Keys keys) {
        static te::Timestamp delay(0.2f);
        static std::size_t entity_proj = PROJ_E;

        if (!keys[te::Key::Space] || !delay.checkDelay())
            return;

        auto &player = getComponent<addon::intact::Player>();
        auto &position = getComponent<addon::physic::Position2>();

        if (entity_proj > MAX_PROJ_E)
            entity_proj = PROJ_E;
        for (auto&& [_, pos] : ECS::DenseZipper(player, position)) {
            createEntity(entity_proj++, "projectile", {pos.x + 10, pos.y});
        }
    });

    state = GameState::RUN;
    te::Timestamp delta(1.0f / 60);
    while (state == GameState::RUN) {
        if (delta.checkDelay())
            runSystems();
    }
}
