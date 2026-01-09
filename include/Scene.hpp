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


/**
 * @brief Phases responsible for system handling priority
 *
 * input -> pre_update -> update -> post_update -> render
 */
enum PHASES : std::size_t {
    INPUT = 0,
    PRE_UPDATE,
    UPDATE,
    POST_UPDATE,
    RENDER,
    PHASE_MAX
};

struct SceneEntity {
    ECS::Entity idx;
    std::string name;
    mat::Vector2f pos;
};

struct Scene {
    std::vector<std::string> signals;
    std::array<std::vector<std::string>, PHASES::PHASE_MAX> systems;
    // std::vector<std::pair<std::string, te::PHASES>> systems;
    std::vector<SceneEntity> entities;
    bool active = false;
};
