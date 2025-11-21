/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** map_loader.cpp
*/

#include "components/map_loader.hpp"

namespace te {

MapLoader::MapLoader(const std::string& path, bool state = false)
    : fpath(path), change(state) {}

void MapLoader::changeMap(const std::string& new_path) {
    fpath = new_path;
    change = true;
}

}  // namespace te

