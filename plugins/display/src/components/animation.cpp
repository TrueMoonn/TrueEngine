/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** animation
*/

#include "display/components/animation.hpp"

namespace addon {
namespace display {

const FrameData &Animation::getCurrentAnim() {
    return frameInfos[curAnim];
}

bool Animation::changeAnimation(size_t index) {
    if (index >= frameInfos.size())
        return false;
    curAnim = index;
    curFrame = 0;
    timestamp.delay = frameInfos[curAnim].frameDELAY;
    timestamp.restart();
    return true;
}

void Animation::increment() {
    curFrame++;
    if (curFrame >= frameInfos[curAnim].frameMAX)
        curFrame = frameInfos[curAnim].loop ? 0 : curFrame - 1;
}

void Animation::decrement() {
    if (curFrame > 0)
        curFrame--;
}

void Animation::pause()
{
    if (!timestamp.isPaused())
        timestamp.toggle();
}

void Animation::unpause()
{
    if (timestamp.isPaused())
        timestamp.toggle();
}

} // namespace display
}  // namespace addon
