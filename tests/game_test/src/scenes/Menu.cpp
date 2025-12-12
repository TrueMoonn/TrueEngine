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
    std::vector<std::string> plugin;
    plugin.emplace_back("sfml");
    plugin.emplace_back("physic");
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
        createComponent("window", SYSTEM_ENTITY);
        toml::table spriteInfo;
        spriteInfo.insert_or_assign("path", BACKGROUND_SPRITE_PATH);
        toml::array spriteSize;
        spriteSize.push_back(1920);
        spriteSize.push_back(1080);
        spriteInfo.insert_or_assign("size", spriteSize);
        createComponent("sprite", ID_MENU_BACKGROUND, spriteInfo);
        createComponent("drawable", ID_MENU_BACKGROUND);
        toml::table position;
        position.insert_or_assign("x", 0);
        position.insert_or_assign("y", 0);
        createComponent("position2", ID_MENU_BACKGROUND, position);

        toml::table spriteButtonStart;
        spriteButtonStart.insert("path", START_SPRITE_PATH);
        toml::array StartSize;
        StartSize.push_back(400);
        StartSize.push_back(100);
        spriteButtonStart.insert_or_assign("size", StartSize);
        toml::table positionStart;
        positionStart.insert_or_assign("x", 100);
        positionStart.insert_or_assign("y", 200);
        createComponent("sprite", ID_MENU_BUTTON_START, spriteButtonStart);
        createComponent("drawable", ID_MENU_BUTTON_START);
        createComponent("clickable", ID_MENU_BUTTON_START);
        createComponent("hoverable", ID_MENU_BUTTON_START);
        createComponent("position2", ID_MENU_BUTTON_START, positionStart);
        // createComponent("hitbox", ID_MENU_BUTTON_START, )
    }
    if (scene == INGAME_ID) {
        // createComponent("window", SYSTEM_ENTITY);

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
            for (int i = (int)ID_MENU_BACKGROUND; i <= (int)ID_MENU_BUTTON_START; i++) {
                removeEntity(i);
                std::cout << "rmv this entity " << i << std::endl;
            }
            setECS(INGAME_ID);
            setEntities(INGAME_ID);
            setEvent(te::event::System::ChangeScene);
        }
    }
}