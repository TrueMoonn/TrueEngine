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

    #define PROJ_E 30000
    #define MAX_PROJ_E 31000
    #define FLASH_E 31001

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

    void run() override;

    void shootProjectile();

 private:
    void setECS(void);
    void setEntities(void);
};
