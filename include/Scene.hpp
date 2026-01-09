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

enum FIELD_STATUS : std::size_t {
    ENTITY,
    SYSTEM,
    SIGNAL,
    FIELD_MAX
};

struct SceneEntity {
    ECS::Entity idx;
    std::string name;
    mat::Vector2f pos;
};

struct Scene {
    std::vector<std::string> signals;
    std::array<std::vector<std::string>, PHASES::PHASE_MAX> systems;
    std::vector<SceneEntity> entities;
    std::array<bool, FIELD_STATUS::FIELD_MAX> active = {false, false, false};
};
