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
#include "sfml/components/text.hpp"

InGame::InGame() : AScene() {
    loadPlugins();
    createComponent("window", SYSTEM_ENTITY);
    addConfig("assets/configs/base.toml");
    addConfig("assets/configs/enemy.toml");
    addConfig("assets/configs/enemy_2.toml");
    addConfig("assets/configs/player.toml");

    te::Scene game;
    game.systems = {{
        {"poll_event"},  // INPUT
        {"follow_player", "parallax_sys"},  // PRE UPDATE
        {"apply_pattern", "movement2", "animate",
            "deal_damage", "apply_fragile"},  // UPDATE
        {"bound_hitbox"},  // POST UPDATE
        {"draw", "draw_text", "display"}  // RENDER
    }};

    size_t map1 = addMap("assets/maps/test1.ddmap");
    ECS::Entity endMap = createMap(MAP_ENTITY_BACKGROUND, map1);

    game.entities = {
        {++endMap, "player", {1920.f / 2, 1080.f / 2}},
        {++endMap, "enemy", {500.f, 500.f}},
        {++endMap, "enemy", {1000.f, 500.f}},
        {++endMap, "enemy", {500.f, 1000.f}},
        {++endMap, "enemy", {600.f, 600.f}},
        {++endMap, "enemy", {1000.0f, 500.0f}},
        {++endMap, "enemy", {1050.0f, 500.0f}},
        {++endMap, "enemy", {1100.0f, 500.0}},
        {800, "background", {0.f, 0.f}}
    };

    activateScene(addScene(game));

    te::Scene menu = {
        {},
        {{
            {"poll_event"},
            {"parallax_sys"},
            {},
            {},
            {"draw", "display"}
        }},
        {
            {801, "background", {1920.f / 2, 1080.f / 2}}
        }
    };
    addScene(menu);
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
    subForScene<te::Keys>(0, "key_input", [this](te::Keys keys){
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
    subForScene<te::Keys>(0, "key_input", [this](te::Keys keys) {
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
    subForScene<te::Keys>(0, "key_input", [this](te::Keys keys) {
        auto &player = getComponent<addon::intact::Player>();
        auto &text = getComponent<addon::sfml::Text>();

        for (auto&& [_, txt] : ECS::DenseZipper(player, text)) {

        for (int key = te::A; key <= te::Z; key += 1)
            if (keys[key])
                txt.str.push_back(keys[te::LeftShift] ? 'A' : 'a' + key);

        if (keys[te::Apostrophe]) txt.str.push_back('4');
        if (keys[te::Hyphen]) txt.str.push_back('6');

        for (int key = te::num0; key <= te::num9; key += 1)
                if (keys[key])
                    txt.str.push_back('0' + key - te::num0);

        if (keys[te::Slash]) txt.str.push_back('/');
        if (keys[te::Add]) txt.str.push_back('+');
        if (keys[te::Multiply]) txt.str.push_back('*');
        if (keys[te::Period]) txt.str.push_back('.');
        if (keys[te::Comma]) txt.str.push_back(',');
        if (keys[te::Space]) txt.str.push_back(' ');

        if (keys[te::Backspace] && !txt.str.empty()) txt.str.pop_back();
        }
    });
    sub<te::Keys>("key_input", [this](te::Keys keys) {
        if (keys[te::Key::P]) {
            pauseScene(0);
            activateScene(1);
        }
        if (keys[te::Key::Escape]) {
            resumeScene(0);
            deactivateScene(1);
        }
    });
    sub<ECS::Entity>("clicked", [](ECS::Entity e) {
        std::cout << "clicked " << e << std::endl;
    });
    sub<ECS::Entity>("hovered", [](ECS::Entity e) {
        std::cout << "hovered " << e << std::endl;
    });

    state = GameState::RUN;
    te::Timestamp delta(1.0f / 60);
    while (state == GameState::RUN) {
        if (delta.checkDelay())
            runSystems();
    }
}
