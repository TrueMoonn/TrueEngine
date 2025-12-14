/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** parallax.hpp
*/

#pragma once

    #include <cstddef>
    #include <maths/Vector.hpp>

namespace addon {
namespace display {

struct Parallax {
    Parallax(std::size_t nb_iterations, const mat::Vector2i& reset);
    Parallax(const Parallax&) = default;
    Parallax(Parallax&&) = default;

    std::size_t iterations;
    mat::Vector2i reset;
};

}  // namespace display
}  // namespace addon
