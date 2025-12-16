/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** sound.cpp
*/

#include <SFML/Audio/Sound.hpp>

#include "sfml/components/sound.hpp"

namespace addon {
namespace sfml {

Sound::Sound(std::string path) : buffer(), sound(buffer) {
    if (!this->buffer.loadFromFile(path))
        return;
    this->sound.setBuffer(this->buffer);
    this->sound.play();
}

Sound::Sound(sf::SoundBuffer buffer_)
    : buffer(std::move(buffer_))
    , sound(buffer)
{
    this->sound.play();
}

Sound::Sound(const Sound& other)
    : buffer(other.buffer)
    , sound(buffer)
{
    sound.setVolume(other.sound.getVolume());
    sound.setPitch(other.sound.getPitch());
    sound.setPlayingOffset(other.sound.getPlayingOffset());
    this->sound.play();
}

Sound& Sound::operator=(const Sound& other) {
    if (this != &other) {
        buffer = other.buffer;
        sound.setBuffer(buffer);
        sound.setVolume(other.sound.getVolume());
        sound.setPitch(other.sound.getPitch());
        sound.setPlayingOffset(other.sound.getPlayingOffset());
    }
    return *this;
}

}  // namespace sfml
}  // namespace addon
