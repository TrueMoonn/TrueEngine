/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** health
*/

#pragma once

    #include <cstdint>

    #include "clock.hpp"
    #include "plugin/plugin_api.hpp"

namespace addon {
namespace eSpec {

struct PLUGIN_API Health {
    explicit Health(const std::int64_t &amount, float delay);
    explicit Health(const std::int64_t &amount, size_t delay);
    void reduceSafely(const std::int64_t &);

    std::int64_t amount;
    te::Timestamp delay;
};

}  // namespace eSpec
}  // namespace addon
