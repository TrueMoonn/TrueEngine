/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** main.cpp
*/

#include <memory>
#include <array>

#include "scenes/InGame.hpp"
#include "scenes/Menu.hpp"

int main(int, const char * const *) {
    std::unique_ptr<IScene> scene = std::make_unique<Menu>();

    scene->run();
    return EXIT_SUCCESS;
}
