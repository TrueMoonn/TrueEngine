/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** health
*/

#pragma once

#include <cstdint>

namespace te {

struct Health {
    explicit Health(const std::int64_t &);
    void reduceSafely(const std::int64_t &);

    std::int64_t  amount;
};

}  // namespace te
