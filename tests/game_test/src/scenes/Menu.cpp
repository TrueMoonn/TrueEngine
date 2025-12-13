/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** Menu.cpp
*/

#include <plugin/PluginManager.hpp>

#include "scenes/Menu.hpp"

#include "sfml/components/sprite.hpp"

Menu::Menu(void) : AScene() {
    loadPlugins();
    setECS(MENU_ID);
    setEntities(MENU_ID);
}

void Menu::setECS(int scene) {
    if (scene == MENU_ID) {
        // createSystem("movement2");
        // createSystem("bound_hitbox");
        // createSystem("follow_player");
        // createSystem("animate");
        createSystem("draw");
        createSystem("display");
    }
    if (scene == INGAME_ID) {
        createSystem("movement2");
        createSystem("bound_hitbox");
        createSystem("follow_player");
        createSystem("animate");
        createSystem("deal_damage");
        createSystem("kill_entity");
        createSystem("draw");
        createSystem("display");
    }
}

void Menu::setEntities(int scene) {
    if (scene == MENU_ID) {
        addConfig("assets/configs/menu.toml");
        addConfig("assets/configs/buttonstart.toml");
        createComponent("window", SYSTEM_ENTITY);
        createEntity(ID_MENU_BACKGROUND + 1, "buttonstart", {800.f, 500.f});
        createEntity(ID_MENU_BACKGROUND, "menu", {0.f, 0.f});
    }
    if (scene == INGAME_ID) {
        addConfig("assets/configs/base.toml");
        addConfig("assets/configs/enemy.toml");
        addConfig("assets/configs/player.toml");

        size_t map1 = addMap("assets/maps/test1.ddmap");
        ECS::Entity endMap = createMap(MAP_ENTITY_BACKGROUND, map1);

        createEntity(endMap + 1, "player", {1920.f / 2, 1080.f / 2});
        createEntity(endMap + 2, "enemy", {500.f, 500.f});
        createEntity(endMap + 3, "enemy", {1000.f, 500.f});
        createEntity(endMap + 4, "enemy", {500.f, 1000.f});
        createEntity(endMap + 5, "enemy", {600.f, 600.f});
    }
}

void Menu::run(void) {
    while (!isEvent(te::event::System::Closed)) {
        pollEvent();
        emit();
        runSystems();
        if (isEvent(te::event::System::ChangeScene)) {
            for (int i = static_cast<int>(ID_MENU_BACKGROUND);
            i <= static_cast<int>(ID_MENU_BUTTON_START); i++)
                removeEntity(i);
            setECS(INGAME_ID);
            setEntities(INGAME_ID);
            setEvent(te::event::System::ChangeScene);
        }
    }
}
