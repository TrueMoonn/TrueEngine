/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** health
*/

#include "entity_spec/components/health.hpp"

namespace addon {
namespace eSpec {

Health::Health(const std::int64_t &amount) :
amount(amount)
{}

void Health::reduceSafely(const std::int64_t &value) {
    amount -= value > amount ? amount : value;
}

}  // namespace eSpec
}  // namespace addon
