/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** fragile
*/

#include "entity_spec/components/fragile.hpp"

namespace addon {
namespace eSpec {

Fragile::Fragile(const std::size_t &p) :
priority(p)
{}

Robust::Robust(const std::size_t &p) :
priority(p)
{}

}  // namespace eSpec
}  // namespace addon
