/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** damage
*/

#pragma once

    #include <cstdint>
    #include <cstddef>

namespace addon {
namespace eSpec {

struct Fragile {
    explicit Fragile(const std::size_t &);

    std::size_t priority;
    std::size_t destroyed = false;
};

struct Robust {
    explicit Robust(const std::size_t &);

    std::size_t priority;
};

}  // namespace eSpec
}  // namespace addon
