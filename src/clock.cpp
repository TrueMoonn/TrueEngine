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
    std::cout << "delay now at " << this->delay << std::endl;
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

void Timestamp::toggle(void) {
    if (this->active)
        this->cur = NOW;
    if (!this->active)
        this->ref = NOW - (this->ref - this->cur);
    this->active = !this->active;
}

microsec Timestamp::getElapsedTime(void) {
    return this->active ? CAST_M(NOW, this->ref) : CAST_M(this->cur, this->ref);
}

}  // namespace te
