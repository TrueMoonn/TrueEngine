/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** clock.cpp
*/

#include "clock.hpp"
#include <iostream>

namespace te {

bool Timestamp::checkDelay(bool restart)
{
    if (this->active && std::clock() - (this->ref + this->delay) > 0) {
        if (restart)
            this->restart();
        return true;
    }
    return false;
}

void Timestamp::restart(void)
{
    this->ref = std::clock();
}

void Timestamp::pause(void)
{
    if (active)
        cur = std::clock();
    if (!active)
        ref = std::clock() - (ref - cur);
    active = !active;
}

double Timestamp::getElapsedTime(void)
{
    return active ? std::clock() - this->ref : this->cur - this->ref;
}

}  // namespace te
