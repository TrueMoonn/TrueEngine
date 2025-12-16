/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** sound.hpp
*/

#pragma once

    #include <SFML/Audio/Sound.hpp>
    #include <SFML/Audio/SoundBuffer.hpp>

namespace addon {
namespace sfml {

struct Sound {
    Sound(std::string path);
    Sound(sf::SoundBuffer buffer);
    Sound(const Sound& other);
    Sound& operator=(const Sound& other);

    Sound(Sound&&) noexcept = default;
    Sound& operator=(Sound&&) noexcept = default;

    sf::SoundBuffer buffer;
    sf::Sound sound;
};
}  // namespace sfml
}  // namespace addon
