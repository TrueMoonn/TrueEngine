/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** paralax.cpp
*/

#include <cstddef>
#include "display/components/paralax.hpp"

namespace addon {
namespace display {

Paralax::Paralax(std::size_t nb_iterations, const mat::Vector2i& reset) :
    iterations(nb_iterations), reset(reset) {}

}  // namespace display
}  // namespace addon
