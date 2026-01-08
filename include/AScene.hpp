/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** AScene.hpp
*/

#pragma once

    #include <vector>
    #include <string>

    #include "GameTool.hpp"
    #include "maths/Vector.hpp"

struct SceneEntity {
    ECS::Entity idx;
    std::string name;
    mat::Vector2f pos;
};

class AScene {
    public:
        AScene() = default;
        ~AScene() = default;

        void setup(te::GameTool &gtool) {
            for (auto &sig : _signals) {
                gtool.addSignals(sig);
            }
            for (auto &sys : _systems) {
                gtool.addSystems(sys);
            }
            for (auto &e : _entities) {
                gtool.createEntity(e.idx, e.name, e.pos);
            }
        };
        void clear(te::GameTool &gtool) {
            for (auto &sig : _signals) {
                gtool.delSignals(sig);
            }
            for (auto &sys : systems) {
                gtool.delSystems(sys);
            }
            for (auto &e : _entities) {
                gtool.removeEntity(e.idx);
            }
        };

    private:
        std::vector<std::string> _signals;
        std::vector<std::string> _systems;
        std::vector<SceneEntity> _entities;
        // std::unordered_map<std::string, std::vector<std::size_t>> mapimapoSystems;
        // std::unordered_map<std::string, std::vector<std::size_t>> mapimapoSignals;
};
