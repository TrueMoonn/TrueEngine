/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** map_loader.cpp
*/

#include <ECS/Zipper.hpp>

#include "components/map_loader.hpp"
#include "systems/map_loader.hpp"

namespace te {

static void load_map(const std::string& fpath) {
    
}

void map_loader(ECS::Registry& reg) {
    auto& mapls = reg.getComponents<MapLoader>();

    for (auto &&[i, loader] : ECS::IndexedZipper(mapls)) {
        if (loader.value().change) {
            load_map(loader.value().fpath);
            loader.value().change = false;
        }
    }
}

}  // namespace te
