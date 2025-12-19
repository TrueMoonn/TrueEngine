/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** hitbox.hpp
*/

#pragma once

#include <ECS/Registry.hpp>
#include <ECS/Entity.hpp>
#include <maths/Rect.hpp>
#include <maths/Vector.hpp>

#include "physic/components/hitbox.hpp"
#include "physic/components/position.hpp"
#include "physic/components/velocity.hpp"

bool square_hitbox(mat::RectF rect1, mat::RectF rect2);

mat::RectF true_hitbox(const addon::physic::Position2 &pos,
    const addon::physic::Hitbox &hit);

std::vector<ECS::Entity> entity_hit_team(ECS::Registry& reg,
    const ECS::Entity& entity);
