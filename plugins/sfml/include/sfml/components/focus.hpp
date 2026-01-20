/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** focus.hpp
*/

#pragma once

namespace addon {
namespace sfml {

struct Focus {
    explicit Focus(bool status) : focus(status) {}
    bool focus = false;
};

}  // namespace sfml
}  // namespace addon
