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

    manager.load("../../../tests/unit_tests/plugins/movement.so");
    EXPECT_EQ(manager.get_handlers().size(), 1);
    EXPECT_NO_THROW(manager.get_handlers().at("movement"));
    EXPECT_THROW(manager.get_handlers().at("none"), std::out_of_range);
}

TEST(DlManager, wrong_load) {
    test_DlManager manager;

    manager.load("../../../tests/unit_tests/plugins/wrong.so");
    EXPECT_THROW(manager.get_handlers().at("wrong"), std::out_of_range);
    EXPECT_EQ(manager.get_handlers().size(), 0);
}

TEST(DlManager, wrong_extension_load) {
    test_DlManager manager;

    manager.load("../../../tests/unit_tests/plugins/movement.png");
    EXPECT_THROW(manager.get_handlers().at("movement"), std::out_of_range);
    EXPECT_EQ(manager.get_handlers().size(), 0);
}

TEST(DlManager, loadDirectory) {
    test_DlManager manager;

    manager.loadDirectory("../../../tests/unit_tests/plugins");
    EXPECT_EQ(manager.get_handlers().size(), 2);
    EXPECT_NO_THROW(manager.get_handlers().at("movement"));
    EXPECT_NO_THROW(manager.get_handlers().at("interaction"));
}

TEST(DlManager, close_handler) {
    test_DlManager manager;

    manager.load("../../../tests/unit_tests/plugins/movement.so");
    manager.closeHandlers("movement");
    EXPECT_THROW(manager.get_handlers().at("movement"), std::out_of_range);
    EXPECT_EQ(manager.get_handlers().size(), 0);
}
