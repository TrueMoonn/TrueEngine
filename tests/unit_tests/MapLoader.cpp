/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** MapLoader.cpp
*/

#include <gtest/gtest.h>

#include "config/map_loader.hpp"

TEST(MapLoader, load_map) {
    te::plugin::PluginManager pmanager;
    ECS::Registry reg;
    te::MapLoader loader;

    EXPECT_NO_THROW(
        loader.loadMap("../../../tests/unit_tests/configs/good.map"));
    auto content = loader.getContent();
    EXPECT_EQ(content.layer_max, 1);
    EXPECT_EQ(content.tilex, 30);
    EXPECT_EQ(content.tiley, 30);
    EXPECT_EQ(content.size, 36);
    int x = (*(content.params.at("G").as_table()))
        ["position2"]["x"].value_or(0);
    EXPECT_EQ(x, 1);
}

TEST(MapLoader, wrong_maps) {
    te::plugin::PluginManager pmanager;
    ECS::Registry reg;
    te::EventManager ev;
    te::MapLoader loader;

    pmanager.loadPlugins(reg, ev, "../../../tests/unit_tests/plugins");
    EXPECT_THROW(
        loader.loadMap("../../../tests/unit_tests/configs/wrong_toml.map"),
        te::MapLoader::LoadError);
    EXPECT_THROW(
        loader.loadMap("../../../tests/unit_tests/configs/no_spliter.map"),
        te::MapLoader::LoadError);
    EXPECT_THROW(
        loader.loadMap("../../../tests/unit_tests/configs/no_entities.map"),
        te::MapLoader::LoadError);
    EXPECT_THROW(loader.loadMap("wrong/path/none.map"),
        te::MapLoader::LoadError);
}
