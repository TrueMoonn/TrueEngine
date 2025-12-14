/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** paralax.hpp
*/

#pragma once

    #include <cstddef>
    #include <maths/Vector.hpp>

namespace addon {
namespace display {

struct Paralax {
    Paralax(std::size_t nb_iterations, std::size_t layer,
        const mat::Vector2i& reset);
    explicit Paralax(const Paralax&);
    explicit Paralax(Paralax&&);

    std::size_t iterations;
    std::size_t layer;
    mat::Vector2i reset;
};

}  // namespace display
}  // namespace addon
