/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** damage
*/

#pragma once

#include <cstdint>

namespace addon {
namespace eSpec {

struct Damage {
    explicit Damage(const std::int64_t &);

    std::int64_t amount;
};

}  // namespace eSpec
}  // namespace addon
