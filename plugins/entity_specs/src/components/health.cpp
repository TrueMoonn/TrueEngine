/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** health
*/

#include "entity_spec/components/health.hpp"

namespace addon {
namespace eSpec {

Health::Health(const std::int64_t &amount, float delay)
    : amount(amount), delay(delay, false) {}

Health::Health(const std::int64_t &amount, std::size_t delay)
    : amount(amount), delay(delay, false) {}

void Health::reduceSafely(const std::int64_t &value) {
    amount -= value > amount ? amount : value;
}

}  // namespace eSpec
}  // namespace addon
