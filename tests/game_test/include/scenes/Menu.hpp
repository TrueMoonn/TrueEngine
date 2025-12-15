/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** Menu.hpp
*/

#pragma once

    #include <map>
    #include <vector>

    #include "scenes/AScene.hpp"
    #include "map_management.hpp"

    #define PLAYER_SPRITE_PATH "assets/test.png"
    #define BACKGROUND_SPRITE_PATH "assets/background.png"
    #define START_SPRITE_PATH "assets/Start.png"
    #define QUIT_SPRITE_PATH "assets/Quit.png"
    #define CONTROLS_SPRITE_PATH "assets/Controls.png"
    #define CLOCK_RATE 1000 / DEFAULT_FRAME_LIMIT

    #define MENU_ID 0
    #define INGAME_ID 1

    #define ID_MENU_BACKGROUND 2000
    #define ID_MENU_BUTTON_START 2001
    #define ID_MENU_BUTTON_SETTINGS 2002
    #define ID_MENU_BUTTON_QUIT 2003

class Menu : public AScene {
 public:
    Menu();
    ~Menu() = default;

    void run() override;
 private:
    void setECS(int scene);
    void setEntities(int scene);
};
