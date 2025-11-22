/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** health
*/

#pragma once

#include <cstddef>

namespace te {

struct Health {
    explicit Health(const std::size_t&);
    void reduceSafely(const std::size_t&);

    std::size_t amount;
};

}  // namespace te
