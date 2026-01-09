/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** map_management.hpp
*/

#pragma once

    #include <string>
    #include <map>
    #include <unordered_map>
    #include <SFML/Graphics/Texture.hpp>
    #include <SFML/Graphics/Image.hpp>

    #include <ECS/Registry.hpp>

    /* Maximim width readed from file */
    #define MAP_MAX_WIDTH 100
    /* Maximum heigth readed from file */
    #define MAP_MAX_HEIGHT 100

    /* Player entity pose in sparse array */
    #define MAP_ENTITY_PLAYER 999
    /* First wall entity pose in sparse array */
    #define MAP_ENTITY_BACKGROUND 1000
    /* Max wall entity in sparse array */
    #define MAP_MAX_ENTITY_BACKGROUND MAP_ENTITY_BACKGROUND \
        + MAP_MAX_WIDTH * MAP_MAX_HEIGHT


    #define SQUARE_WIDTH 50
    #define SQUARE_HEIGHT 50

/* Extention for map initialisation */
static const char *MAP_EXTENTION(".ddmap");
static const std::size_t MAP_EXTENTION_SIZE(7);

enum MAP_TYPES : char {
    MAP_WALL = 'X',
    MAP_PLAYER = 'P',
    MAP_DOOR = 'D',
};

static const std::map<std::string, std::string> MAPS_PATHS = {
    {"test1", "./assets/maps/test1.ddmap"},
    {"test2", "./assets/maps/test2.ddmap"},
};

static const std::unordered_map<MAP_TYPES, sf::Image> TEMP_MAP_IMAGE {
    {MAP_WALL, sf::Image(sf::Vector2u(SQUARE_WIDTH, SQUARE_HEIGHT),
        sf::Color::Red)},
    {MAP_DOOR, sf::Image(sf::Vector2u(SQUARE_WIDTH, SQUARE_HEIGHT),
        sf::Color::Blue)},
    {MAP_PLAYER, sf::Image(sf::Vector2u(30, 30), sf::Color::Yellow)}
};
