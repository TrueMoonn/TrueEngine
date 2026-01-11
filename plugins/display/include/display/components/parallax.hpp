/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** parallax.hpp
*/

#pragma once

    #include <cstddef>
    #include <maths/Vector.hpp>

    #include "plugin/plugin_api.hpp"

namespace addon {
namespace display {

struct PLUGIN_API Parallax {
    Parallax(std::size_t nb_iterations, const mat::Vector2i& reset);
    Parallax(const Parallax&) = default;
    Parallax(Parallax&&) = default;
    Parallax& operator=(const Parallax& other) = default;
    Parallax& operator=(Parallax&& other) noexcept = default;

    std::size_t iterations;
    mat::Vector2i reset;
};

}  // namespace display
}  // namespace addon
