/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** clock.hpp
*/

#pragma once

#include <chrono>

namespace te {

#define SEC_TO_MICRO(t) (t * 1000000)

#define NOW std::chrono::steady_clock::now()
#define CAST_M(a, b) \
    std::chrono::duration_cast<std::chrono::microseconds>(a - b).count()

typedef std::chrono::steady_clock::time_point delta_t;

typedef int64_t microsec;

struct Timestamp {
 public:
    explicit Timestamp(float delay, bool active = true)
        : delay(size_t(SEC_TO_MICRO(delay)))
        , ref(NOW), cur(ref), active(active) {}

    microsec getElapsedTime(void);
    bool checkDelay(bool restart = true);
    void restart(void);
    void pause(void);
    bool isPaused(void) { return !active; }

    microsec delay;

 private:
    bool active;
    delta_t ref;
    delta_t cur;
};

}  // namespace te
