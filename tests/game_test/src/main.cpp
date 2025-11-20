/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** main.cpp
*/

#include <iostream>
#include <ECS/Registry.hpp>

#include "game.hpp"

int main(void) {
    ECS::Registry reg;

    auto& ints = reg.registerComponent<int>();
    reg.addComponent<int>(3, 4);

    reg.addSystem([](ECS::Registry& reg){std::cout << "hihi" << std::endl;});

    std::cout << ints[3].value() << std::endl;
    reg.runSystems();
    return 0;
}
