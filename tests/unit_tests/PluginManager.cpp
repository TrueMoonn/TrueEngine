/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** PluginManager.cpp
*/

#include <vector>
#include <string>

#include <gtest/gtest.h>

#include <ECS/Registry.hpp>
#include <toml++/toml.hpp>
#include "plugin/PluginManager.hpp"

#include "movement/components/position.hpp"

TEST(PluginManager, load_plugins) {
    ECS::Registry reg;
    te::PluginManager::loadPlugins(reg, "../../../tests/unit_tests/plugins");
    std::vector<std::string> names = te::PluginManager::getPlugins();

    EXPECT_EQ(names.size(), 2);
    EXPECT_TRUE(names[0].compare("movement"));
    EXPECT_TRUE(names[1].compare("interaction"));
}

// TEST(PluginManager, clear) {
//     ECS::Registry reg;
//     te::PluginManager::loadPlugins(reg, "../../../tests/unit_tests/plugins");
//     te::PluginManager::clear();
//     std::vector<std::string> names = te::PluginManager::getPlugins();
//     EXPECT_EQ(names.size(), 0);
// }

TEST(PluginManager, component_loading) {
    ECS::Registry reg;
    te::PluginManager::loadPlugins(reg, "../../../tests/unit_tests/plugins");

    toml::table table =
        toml::parse_file("../../../tests/unit_tests/configs/position.toml");
    EXPECT_TRUE(te::PluginManager::loadComponent("position2", 0, table));
    EXPECT_EQ(reg.getComponents<te::Position2>().size(), 1);
    EXPECT_FALSE(te::PluginManager::loadComponent("wrong", 0));
}
