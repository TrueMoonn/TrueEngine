/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** audio.hpp
*/

#pragma once

    #include <string>

    #include <SFML/Audio/Sound.hpp>
    #include <SFML/Audio/SoundBuffer.hpp>

    #include "plugin/plugin_api.hpp"

namespace addon {
namespace sfml {

struct PLUGIN_API Sound : sf::Sound {
    Sound(const sf::SoundBuffer &buffer, bool loop = false, bool isPlaying = false);

    bool loop;
    bool isPlaying;
    int64_t curProgress;
};

}  // namespace sfml
}  // namespace addon
