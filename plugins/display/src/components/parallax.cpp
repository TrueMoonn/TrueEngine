/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** parallax.cpp
*/

#include <cstddef>
#include "display/components/parallax.hpp"

namespace addon {
namespace display {

Parallax::Parallax(std::size_t nb_iterations, const mat::Vector2i& reset) :
    iterations(nb_iterations), reset(reset) {}

}  // namespace display
}  // namespace addon
