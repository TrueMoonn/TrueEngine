/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** PluginManage.cpp
*/

#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

#include "plugin/DlManager.hpp"

class test_DlManager : public te::DlManager {
 public:
    std::unordered_map<std::string, void *> get_handlers() {
        return _handles;
    }
};

TEST(DlManager, load) {
    test_DlManager manager;

    manager.load("../../../tests/unit_tests/plugins/physic.so");

    EXPECT_EQ(manager.get_handlers().size(), 1);
    EXPECT_NO_THROW(manager.get_handlers().at("physic"));

    auto names = manager.getNames();
    EXPECT_EQ(names.size(), 1);
    EXPECT_EQ(names[0], "physic");

    EXPECT_THROW(manager.get_handlers().at("none"), std::out_of_range);
}

TEST(DlManager, loadDirectory) {
    test_DlManager manager;

    manager.loadDirectory("../../../tests/unit_tests/plugins");
    EXPECT_EQ(manager.get_handlers().size(), 2);
    EXPECT_NO_THROW(manager.get_handlers().at("physic"));
    EXPECT_NO_THROW(manager.get_handlers().at("interaction"));
}

TEST(DlManager, wrong_load) {
    test_DlManager manager;

    manager.load("../../../tests/unit_tests/plugins/wrong.so");
    EXPECT_THROW(manager.get_handlers().at("wrong"), std::out_of_range);
    EXPECT_EQ(manager.get_handlers().size(), 0);
}

TEST(DlManager, wrong_extension_load) {
    test_DlManager manager;

    manager.load("../../../tests/unit_tests/plugins/physic.png");
    EXPECT_THROW(manager.get_handlers().at("physic"), std::out_of_range);
    EXPECT_EQ(manager.get_handlers().size(), 0);
}

TEST(DlManager, wrong_symbol_access) {
    test_DlManager manager;

    manager.load("../../../tests/unit_tests/plugins/physic.so");
    EXPECT_THROW(manager.access<int(*)(void)>("physic", "wrong"),
        std::runtime_error);
}

TEST(DlManager, close_handler) {
    test_DlManager manager;

    manager.load("../../../tests/unit_tests/plugins/physic.so");
    manager.closeHandlers("physic");
    EXPECT_THROW(manager.get_handlers().at("physic"), std::out_of_range);
    EXPECT_EQ(manager.get_handlers().size(), 0);
}
