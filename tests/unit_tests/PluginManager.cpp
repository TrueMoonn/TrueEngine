/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** PluginManager.cpp
*/

#include <gtest/gtest.h>
#include <vector>
#include <string>

#include <ECS/Registry.hpp>
#include <toml++/toml.hpp>
#include "plugin/PluginManager.hpp"

#include "physic/components/position.hpp"

TEST(PluginManager, load_plugins) {
    te::plugin::PluginManager pmanager;
    ECS::Registry reg;
    te::EventManager ev;
    pmanager.loadPlugins(reg, ev, "../../../tests/unit_tests/plugins");
    std::vector<std::string> names = pmanager.getPlugins();

    EXPECT_EQ(names.size(), 2);
    EXPECT_TRUE(names[0].compare("physic"));
    EXPECT_TRUE(names[1].compare("interaction"));
}

TEST(PluginManager, clear) {
    te::plugin::PluginManager pmanager;
    ECS::Registry reg;
    te::EventManager ev;
    pmanager.loadPlugins(reg, ev, "../../../tests/unit_tests/plugins");
    pmanager.clear();
    std::vector<std::string> names = pmanager.getPlugins();
    EXPECT_EQ(names.size(), 0);
}

TEST(PluginManager, component_loading) {
    te::plugin::PluginManager pmanager;
    ECS::Registry reg;
    te::EventManager ev;
    pmanager.loadPlugins(reg, ev, "../../../tests/unit_tests/plugins");

    toml::table table =
        toml::parse_file("../../../tests/unit_tests/configs/position.toml");
    EXPECT_NO_THROW(pmanager.loadComponent("position2", 0, table));
    EXPECT_EQ(reg.getComponents<addon::physic::Position2>().size(), 1);
    EXPECT_THROW(pmanager.loadComponent("wrong", 0, {}),
        te::plugin::PluginManager::NoPluginFound);
}

TEST(PluginManager, system_loading) {
    te::plugin::PluginManager pmanager;
    ECS::Registry reg;
    te::EventManager ev;
    pmanager.loadPlugins(reg, ev, "../../../tests/unit_tests/plugins");

    EXPECT_NO_THROW(pmanager.loadSystem("movement2"));
    EXPECT_THROW(pmanager.loadSystem("wrong"),
        te::plugin::PluginManager::NoPluginFound);
}
