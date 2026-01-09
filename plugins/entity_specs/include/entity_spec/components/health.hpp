/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** health
*/

#pragma once

#include <cstdint>

#include "clock.hpp"

namespace addon {
namespace eSpec {

struct Health {
    explicit Health(const std::int64_t &amount, float delay);
    explicit Health(const std::int64_t &amount, std::size_t delay);
    void reduceSafely(const std::int64_t &);

    std::int64_t amount;
    te::Timestamp delay;
};

}  // namespace eSpec
}  // namespace addon
