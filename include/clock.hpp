/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** clock.hpp
*/

#pragma once

#include <chrono>

namespace te {

typedef std::clock_t delta;

#define SEC_TO_MICRO(t) (t * 1000000)

struct Timestamp {
 public:
    Timestamp(delta delay, bool active = true)
        : delay(delay), ref(std::clock()), cur(std::clock()), active(active) {}

    double getElapsedTime(void);
    bool checkDelay(bool restart = true);
    void restart(void);
    void pause(void);
    bool isPaused(void) { return !active; }

    delta delay;

 private:
    bool active;
    delta ref;
    delta cur;
};

}  // namespace te
