/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** sprite.cpp
*/

#include <iostream>
#include <string>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Listener.hpp>

#include "sfml/components/sound.hpp"

namespace addon {
namespace sfml {

Sound::Sound(const sf::SoundBuffer &buffer, bool loop, bool isPlaying)
    : sf::Sound(buffer), loop(loop), isPlaying(isPlaying), curProgress(0) {
    this->setLooping(loop);
    if (isPlaying) this->play();
}

} // namespace sfml
}  // namespace addon
