/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** clock.cpp
*/

#include "clock.hpp"
#include <iostream>

namespace te {

bool Timestamp::checkDelay(bool restart) {
    if (this->active && CAST_M(NOW, this->ref) > this->delay) {
        if (restart)
            this->restart();
        return true;
    }
    return false;
}

void Timestamp::restart(void) {
    this->ref = NOW;
}

void Timestamp::pause(void) {
    if (active)
        cur = NOW;
    if (!active)
        ref = NOW - (ref - cur);
    active = !active;
}

microsec Timestamp::getElapsedTime(void) {
    return active ? CAST_M(NOW, this->ref) : CAST_M(this->cur, this->ref);
}

}  // namespace te
