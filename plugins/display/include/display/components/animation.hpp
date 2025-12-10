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

namespace addon {
namespace display {

typedef std::array<size_t, 2> pos;

/**
 * @brief Animation frame data (duration and delay)
 */
struct FrameData {
    FrameData(const pos &position, size_t max, float delay, bool loop = true)
        : frameBEG(position), frameMAX(max)
        , frameDELAY(SEC_TO_MICRO(delay)), loop(loop) {}

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
        : frameInfos(std::move(frameInfos)), curAnim(0), curFrame(0)
        , timestamp(frameInfos.at(0).frameDELAY) {}

    Animation(const Animation &other) : frameInfos(other.frameInfos),
        curAnim(other.curAnim), curFrame(other.curFrame), timestamp(other.timestamp) {}

    Animation(Animation &&other) : frameInfos(std::move(other.frameInfos)),
        curAnim(std::move(other.curAnim)), curFrame(std::move(other.curFrame)),
        timestamp(std::move(other.timestamp))
        {}

    ~Animation() = default;

    const FrameData &getCurrentAnim();
    bool changeAnimation(size_t index);
    void increment();
    void decrement();
    void pause();
    void unpause();

    const std::vector<FrameData> frameInfos;
    std::size_t curAnim;
    std::size_t curFrame;

    te::Timestamp timestamp;
};

}  // namespace display
}  // namespace addon
