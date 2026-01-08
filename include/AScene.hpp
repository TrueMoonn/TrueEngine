/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** AScene.hpp
*/

#pragma once

    #include <vector>
    #include <string>

    #include <ECS/Entity.hpp>

    #include "maths/Vector.hpp"

struct SceneEntity {
    ECS::Entity idx;
    std::string name;
    mat::Vector2f pos;
};

struct AScene {
    std::vector<std::string> signals;
    std::vector<std::string> systems;
    std::vector<SceneEntity> entities;
};
