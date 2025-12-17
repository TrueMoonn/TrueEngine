/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** timeout
*/

#pragma once

#include "clock.hpp"

namespace addon {
namespace eSpec {

struct Timeout {
    explicit Timeout(float time_to_death);

    te::Timestamp delta;
};

}  // namespace eSpec
}  // namespace addon
