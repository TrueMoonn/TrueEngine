/*
** EPITECH PROJECT, 2025
** DeepestDungeonGAME
** File description:
** movable
*/

#pragma once

namespace addon {
namespace physic {

/**
 * @brief Stationary and Movable components
 *
 */

/**
 * @brief Component indicating that the entity can be moved by
 *  "stationary" components
 */
struct Movable {
    unsigned movable = 1;
};

/**
 * @brief Component indicating that the entity can move "movable" components
 */
struct Stationary {
    unsigned stationary = 1;
};

}  // namespace physic
}  // namespace addon
