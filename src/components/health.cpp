/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** health
*/

#include "components/health.hpp"

namespace te
{

Health::Health(const std::size_t &amount) :
amount(amount)
{}

void Health::reduceSafely(const std::size_t &value)
{
    amount -= value > amount ? amount : value;
}

} // namespace te
