/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** InGame.cpp
*/

#include "scenes/in_game/InGame.hpp"

#include "scenes/in_game/in_game.cpmt.hpp"
#include "scenes/in_game/in_game.sys.hpp"
#include "components/clock.hpp"

InGame::InGame() {
    setECS();
    setEntities();
}

void InGame::setECS(void) {
    _reg.registerComponent<te::Drawable>();
    _reg.registerComponent<te::Position2>();
    _reg.registerComponent<te::Movable>();
    _reg.registerComponent<te::Velocity2>();
    _reg.registerComponent<te::Sprite>();
    _reg.registerComponent<te::Health>();
    _reg.registerComponent<te::Damage>();
    _reg.registerComponent<te::Window>();
    _reg.registerComponent<te::Player>();
    _reg.registerComponent<te::Hitbox>();
    _reg.registerComponent<te::Interactive>();

    _reg.addSystem(&te::movement2_sys);
    _reg.addSystem(&te::deal_damage);
    _reg.addSystem(&te::hitbox2_sys);
    _reg.addSystem(&te::player_interaction_sys);
    _reg.addSystem(&te::manageEvent);
    _reg.addSystem(&te::follow_player_sys);
    _reg.addSystem(&te::draw_sys);
    _reg.addSystem(&te::display_sys);
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
