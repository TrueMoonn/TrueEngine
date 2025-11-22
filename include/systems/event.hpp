/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** event.hpp
*/

#pragma once

    #include <map>
    #include <SFML/System/Vector2.hpp>
    #include <SFML/Window/Keyboard.hpp>

    #include <SFML/Graphics/Image.hpp>
    #include <SFML/Graphics/Texture.hpp>

    #include <ECS/Registry.hpp>

namespace te {

    #define PROJ_VEL 3.0f
    #define PROJ_SIZE 10.0f

    #define PROJ_VAL 20000
    #define PROJ_MAX_VAL 21000


    const sf::Texture PROJ_TEXT(sf::Image(sf::Vector2u(PROJ_SIZE, PROJ_SIZE),
        sf::Color::Green));

enum player_movement_e {
    P_LEFT_MOV = static_cast<int>(sf::Keyboard::Key::Q),
    P_RIGHT_MOV = static_cast<int>(sf::Keyboard::Key::D),
    P_TOP_MOV = static_cast<int>(sf::Keyboard::Key::Z),
    P_BOT_MOV = static_cast<int>(sf::Keyboard::Key::S),
};

    #define P_MOV_FACTOR 3.0f


static const std::map<player_movement_e, float> P_MOVEMENT = {
    {P_LEFT_MOV, -P_MOV_FACTOR},
    {P_RIGHT_MOV, P_MOV_FACTOR},
    {P_TOP_MOV, -P_MOV_FACTOR},
    {P_BOT_MOV, P_MOV_FACTOR},
};

void manageEvent(ECS::Registry& reg);

}  // namespace te
