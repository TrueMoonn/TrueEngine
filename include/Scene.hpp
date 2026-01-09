/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** AScene.hpp
*/

#pragma once

    #include <vector>
    #include <string>
    #include <functional>
    #include <set>

    #include <ECS/Entity.hpp>

    #include "maths/Vector.hpp"

struct Scene {
    enum class SceneState {
        INACTIVE,
        ACTIVE,
        PAUSED
    };
    SceneState state = SceneState::INACTIVE;

    enum PHASES : std::size_t {
        INPUT = 0,
        PRE_UPDATE,
        UPDATE,
        POST_UPDATE,
        RENDER,
        PHASE_MAX
    };
    std::array<std::vector<std::string>, PHASES::PHASE_MAX> systems;

    struct SceneEntity {
        ECS::Entity idx;
        std::string name;
        mat::Vector2f pos;
    };
    std::vector<SceneEntity> entities;
};
