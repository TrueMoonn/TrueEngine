/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** animation
*/

#include "display/components/animation.hpp"

namespace te
{

const FrameData &te::Animation::getCurrentAnim()
{
    return frameInfos[curAnim];
}

bool te::Animation::changeAnimation(size_t index)
{
    if (index >= frameInfos.size())
        return false;
    curAnim = index;
    curFrame = 0;
    return true;
}

void te::Animation::increment()
{
    curFrame++;
    if (curFrame >= frameInfos[curAnim].frameMAX)
        curFrame = frameInfos[curAnim].loop ? 0 : curFrame - 1;
}

void Animation::decrement()
{
    if (curFrame > 0)
        curFrame--;
}

} // namespace te
