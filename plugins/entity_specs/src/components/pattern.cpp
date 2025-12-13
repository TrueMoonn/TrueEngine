/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** pattern
*/

#include <array>

#include "entity_spec/components/pattern.hpp"

#include "clock.hpp"

namespace addon {
namespace eSpec {

Pattern::Pattern(std::size_t index, float amp, float freq)
    : amplitude(amp), frequency(freq)
    , func(index > MAX_PATTERN ? patterns[DEFAULT] : patterns[index]) {}

}  // namespace eSpec
}  // namespace addon
