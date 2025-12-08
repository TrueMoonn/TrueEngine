/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Animation
*/

#pragma once

#include <vector>
#include <cstddef>
#include <array>
#include <utility>
#include <chrono>

#include "clock.hpp"

#define STM(sec) (sec * 1000000)

namespace addon {
namespace display {

typedef std::array<size_t, 2> pos;

/**
 * @brief Animation frame data (duration and delay)
 */
struct FrameData {
    FrameData(const pos &position, size_t max, float delay, bool loop = true)
        : frameBEG(position), frameMAX(max)
        , frameDELAY(STM(delay)), loop(loop) {}

    pos frameBEG;
    size_t frameMAX;
    size_t frameDELAY;
    bool loop;
};

/**
 * @brief Animation handling component
 *
 * Handles animations via a number of frames, 0 being the default
 */
struct Animation {
    /**
     * @brief Animation Constructor
     *
     * @param frameinfos
     *  FrameData vector containing each animation and its duration.
     *
     */
    explicit Animation(const std::vector<FrameData> &frameInfos)
        : frameInfos(std::move(frameInfos)), curAnim(0), curFrame(0) {}

    Animation(const Animation &other) : frameInfos(other.frameInfos),
        curAnim(other.curAnim), curFrame(other.curFrame), delta(other.delta) {}

    Animation(Animation &&other) : frameInfos(std::move(other.frameInfos)),
        curAnim(std::move(other.curAnim)), curFrame(std::move(other.curFrame)),
        delta(std::move(other.delta))
        {}

    ~Animation() = default;

    const FrameData &getCurrentAnim();
    bool changeAnimation(size_t index);
    void increment();
    void decrement();

    const std::vector<FrameData> frameInfos;
    std::size_t curAnim;
    std::size_t curFrame;

    te::delta_t delta;
};

}  // namespace display
}  // namespace addon
