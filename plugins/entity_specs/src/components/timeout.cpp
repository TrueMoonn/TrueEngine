/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** fragile
*/

#include "entity_spec/components/timeout.hpp"

namespace addon {
namespace eSpec {

Timeout::Timeout(float time_to_death)
    : delta(time_to_death) {}

}  // namespace eSpec
}  // namespace addon
