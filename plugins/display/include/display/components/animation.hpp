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
#include "maths/Vector.hpp"
#include "plugin/plugin_api.hpp"

namespace addon {
namespace display {

/**
 * @brief Animation frame data (duration and delay)
 */
struct PLUGIN_API FrameData {
    FrameData(const mat::Vector2<size_t> &position, size_t max,
            float delay, bool loop = true)
        : frameBEG(position), frameMAX(max)
        , frameDELAY(SEC_TO_MICRO(delay)), loop(loop) {}

    FrameData(const FrameData&) = default;
    FrameData(FrameData&&) noexcept = default;
    FrameData& operator=(const FrameData& other) = default;
    FrameData& operator=(FrameData&& other) noexcept = default;

    mat::Vector2<size_t> frameBEG;
    size_t frameMAX;
    size_t frameDELAY;
    bool loop;
};

/**
 * @brief Animation handling component
 *
 * Handles animations via a number of frames, 0 being the default
 */
struct PLUGIN_API Animation {
    /**
     * @brief Animation Constructor
     *
     * @param frameinfos
     *  FrameData vector containing each animation and its duration.
     *
     */
    explicit Animation(const std::vector<FrameData> &frameInfos)
        : frameInfos(frameInfos), curAnim(0), curFrame(0)
        , timestamp(frameInfos.at(0).frameDELAY) {}

    Animation(const Animation &other) : frameInfos(other.frameInfos)
        , curAnim(other.curAnim), curFrame(other.curFrame)
        , timestamp(other.timestamp) {}

    Animation(Animation &&other) : frameInfos(std::move(other.frameInfos)),
        curAnim(other.curAnim), curFrame(other.curFrame),
        timestamp(std::move(other.timestamp)) {}

    Animation& operator=(const Animation& other) = default;
    Animation& operator=(Animation&& other) noexcept = default;

    ~Animation() = default;

    const FrameData &getCurrentAnim();
    bool changeAnimation(size_t index);
    void increment();
    void decrement();
    void pause() { if (!timestamp.isPaused()) timestamp.toggle(); }
    void unpause() { if (timestamp.isPaused()) timestamp.toggle(); }
    void toggle() { this->timestamp.toggle(); }

    std::vector<FrameData> frameInfos;
    std::size_t curAnim;
    std::size_t curFrame;

    te::Timestamp timestamp;
};

}  // namespace display
}  // namespace addon
