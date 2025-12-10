/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** team
*/

#pragma once

#include <string>

namespace addon {
namespace eSpec {

struct Team {
    explicit Team(const std::string &teamName);

    std::string name;
};

}  // namespace eSpec
}  // namespace addon
