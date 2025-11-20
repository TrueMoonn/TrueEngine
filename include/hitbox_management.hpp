/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** hitbox_management.hpp
*/

#pragma once

    #include <vector>

    #include <ECS/Registry.hpp>

std::vector<ECS::Entity> entity_hit(ECS::Registry& reg,
    const ECS::Entity entity);
void entity_interaction(ECS::Registry& reg, const ECS::Entity entity);
