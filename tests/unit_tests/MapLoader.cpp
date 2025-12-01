/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** MapLoader.cpp
*/

#include <gtest/gtest.h>

#include <ECS/Registry.hpp>
#include "plugin/PluginManager.hpp"

#include "config/map_loader.hpp"

TEST(MapLoader, wrong_filepath) {
    ECS::Registry reg;
    te::MapLoader loader(0, 16);

    EXPECT_THROW(loader.loadMap(reg, "this/lead/to/nowhere"),
        te::MapLoader::FileNotFound);
}

TEST(MapLoader, no_separator) {
    ECS::Registry reg;
    te::MapLoader loader(0, 16);

    EXPECT_THROW(loader.loadMap(reg, "../../../tests/unit_tests/assets/no_sep.tem"),
        te::MapLoader::ParsingError);
}

TEST(MapLoader, no_entities) {
    ECS::Registry reg;
    te::MapLoader loader(0, 16);

    EXPECT_THROW(
        loader.loadMap(reg, "../../../tests/unit_tests/assets/no_entities.tem"),
        te::MapLoader::ParsingError);
}

TEST(MapLoader, good_file) {
    ECS::Registry reg;
    te::PluginManager::loadPlugins(reg, "../../../tests/unit_tests/plugins");
    te::MapLoader loader(0, 16);

    EXPECT_NO_THROW(loader.loadMap(reg, "../../../tests/unit_tests/assets/map.tem"));
}

