/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** InGame.hpp
*/

#pragma once

    #include "scenes/AScene.hpp"
    #include "map_management.hpp"

    #define PLAYER_SPRITE_PATH "assets/test.png"
    #define CLOCK_RATE 1000 / DEFAULT_FRAME_LIMIT

enum IG_entities_e : ECS::Entity {
    MAIN_WINDOW = 0,
    PLAYER = MAP_ENTITY_PLAYER,
    MIN_BG = MAP_ENTITY_BACKGROUND,
    MAX_BG = MAP_MAX_ENTITY_BACKGROUND,
};

class InGame : public AScene {
 public:
    InGame();
    ~InGame() = default;

 private:
    void setECS(void);
    void setEntities(void);
};
