/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** clock.hpp
*/

#pragma once

#include <chrono>
#include <utility>

namespace te {

#define SEC_TO_MICRO(t) (t * 1000000)

#define NOW std::chrono::steady_clock::now()
#define CAST_M(a, b) \
    std::chrono::duration_cast<std::chrono::microseconds>(a - b).count()

typedef std::chrono::steady_clock::time_point delta_t;

typedef int64_t microsec;

/**
 * @brief Timestamp class for delta time handling in microseconds
 */
class Timestamp {
 public:
    /**
     * @param delay The delay in microseconds until the next trigger is reached
     * @param active Weither the clock should start right away or not
     */
    explicit Timestamp(size_t delay, bool active = true)
        : delay(delay) , ref(NOW), cur(ref), active(active) {}


    /**
     * @param delay The delay in seconds until the next trigger is reached
     * @param active Weither the clock should start right away or not
     */
    explicit Timestamp(float delay, bool active = true)
        : delay(size_t(SEC_TO_MICRO(delay)))
        , ref(NOW), cur(ref), active(active) {}


    Timestamp(const Timestamp &other)
        : delay(size_t(other.delay))
        , ref(other.ref), cur(other.cur), active(other.active) {}

    Timestamp(const Timestamp &&other)
        : delay(std::move(size_t(other.delay)))
        , ref(std::move(other.ref)), cur(std::move(other.cur))
        , active(std::move(other.active)) {}

    Timestamp& operator=(const Timestamp& other) = default;
    Timestamp& operator=(Timestamp&& other) noexcept = default;

    microsec getElapsedTime(void);
    bool checkDelay(bool restart = true);
    void restart(void);
    void toggle(void);
    bool isPaused(void) { return !active; }

    microsec delay;

 private:
    bool active;
    delta_t ref;
    delta_t cur;
};

}  // namespace te
