/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Animation
*/

#pragma once

#include <cstddef>
#include <functional>

#include "maths/Vector.hpp"

#include "physic/components/position.hpp"

namespace addon {
namespace eSpec {

struct Pattern {
    explicit Pattern(std::size_t index);

    std::function<float(float)> func;
};

}  // namespace display
}  // namespace addon
