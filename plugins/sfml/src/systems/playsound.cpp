/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** playsound.cpp
*/

#include <ECS/Zipper.hpp>

#include "sfml/components/sound.hpp"
#include "sfml/systems/playsound.hpp"

namespace addon {
namespace sfml {

// void playsound_sys(ECS::Registry& reg) {
//     auto& sounds = reg.getComponents<Sound>();
//     static int idx = 0;

//     for (auto &&[snd] :
//         ECS::Zipper(sounds)) {
//             if (idx == 0)
//                 snd.sound.play();
//             idx++;
//     }
// }

}  // namespace sfml
}  // namespace addon
