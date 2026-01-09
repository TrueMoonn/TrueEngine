/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Animation
*/

#pragma once

#include <cstddef>
#include <functional>
#include <array>
#include <cmath>

#include "clock.hpp"
#include "maths/numeric.hpp"

#include "maths/Vector.hpp"

#include "physic/components/position.hpp"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace addon {
namespace eSpec {

#define F_SEC(val) (static_cast<float>(val) / 1000000)
/**
 * @brief Pattern types available to the user
 */
enum PATTERNS {
    DEFAULT,
    SINE,
    ZIG_ZAG,
    DRUNK,
    MAX_PATTERN
};

/**
 * @brief Patterns
 */
static const std::array<std::function<float(float)>, MAX_PATTERN> patterns {
    [](float freq)->float { return 0; },
    [](float freq)->float {
        static te::Timestamp t(size_t(0));
        return std::sin
            (2.f * M_PI * F_SEC(t.getElapsedTime()) * freq);
    },
    [](float freq)->float {
        static te::Timestamp t(size_t(0));
        return std::fmod
            (F_SEC(t.getElapsedTime()), freq) > 0.5 * freq ? -1.f : 1.f;
    },
    [](float freq)->float {
        static te::Timestamp t(size_t(0));
        float phase = std::sin(F_SEC(t.getElapsedTime()) * 12.f) * 2.f;
        return (std::sin
            (2.f * M_PI * F_SEC(t.getElapsedTime()) + phase * freq));
    },
};

/**
 * @brief Pattern component, allows entities to follow a scripted path
 *        influenced by a mathematical formula
 */
struct Pattern {
    explicit Pattern(std::size_t index, float amplitude = 1,
        float frequency = 1);

    std::function<float(float)> func;
    float amplitude;
    float frequency;
};

}  // namespace eSpec
}  // namespace addon
