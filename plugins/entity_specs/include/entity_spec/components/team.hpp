/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** team
*/

#pragma once

#include <cstdint>

namespace addon {
namespace eSpec {

struct Team {
    explicit Team(const std::int64_t &);

    std::int64_t team;
};

}  // namespace eSpec
}  // namespace addon
