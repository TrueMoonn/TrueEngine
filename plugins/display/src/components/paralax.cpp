/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** paralax.cpp
*/

#include <utility>
#include <cstddef>
#include "display/components/paralax.hpp"

namespace addon {
namespace display {

Paralax::Paralax(std::size_t nb_iterations,
    const mat::Vector2i& reset) :
    iterations(nb_iterations), reset(reset) {}

Paralax::Paralax(const Paralax& other) :
    iterations(other.iterations),
    reset(other.reset) {}

Paralax::Paralax(Paralax&& other) :
    iterations(std::move(other.iterations)),
    reset(std::move(other.reset)) {}

}  // namespace display
}  // namespace addon
