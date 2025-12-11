# TrueEngine

TrueEngine is a user friendly game engine using ECS as base implementation.

This engine offer you a fast learning experience in creating offline game
as well as online game giving you easy access to Network and Plugin
management.

## Short usage examples

Here you can follow a quick exemples of TrueEngine usage. Feel free to
follow each steps to create your own game.

For this exemple we will need some extra configuration:
* Graphic Lib Plugin - to use as a window manager
* Toml - file used as a configuration file
* Map - as a txt file to create a simple map

### Main with GameTool

```c++
#include <event/events.hpp>
#include <GameTool.hpp>

int main(void) {
    te::GameTool gtool;

    /* Using plugin manager to interact with dynamic libs */
    // Load plugins from directory
    gtool.loadPlugins("path/to/plugin/folder/");

    // Create system from plugin
    gtool.createSystem("draw");
    gtool.createSystem("display");

    // Create component from plugin
    gtool.createComponent("window", 0);

    /* Using config reader to create entities and maps */
    // Add entities configs
    gtool.addConfig("path/to/config.toml");
    // Add map config
    std::size_t map1_index = gtool.addMap("path/to/map.txt");
    // Load directly a complete map
    auto end_map_index = gtool.createMap(map1_index, 1);
    // or Create entity based on config
    gtool.createEntity(end_map_index + 1, "entity_name");

    /* Main loop */
    while (!gtool.isEvent(te::event::System::Closed)) {
        // Use function pollEvent from graphic lib plugin
        gtool.pollEvent();
        gtool.emit();
        // Run systems loaded
        gtool.runSystems();
    }
    return 0;
}

```

### Main without GameTool

```c++
#include <iostream>

#include "event/EventManager.hpp"
#include <ECS/Registry.hpp>
#include <plugin/PluginManager.hpp>

int main(void) {
    te::plugin::PluginManager pmanager;
    te::event::EventManager emanager;
    ECS::Registry reg;

    pmanager.loadPlugins(reg, emanager, "./plugins/");
    try {
        pmanager.loadSystem("draw");
        pmanager.loadSystem("display");
    } catch (const te::plugin::PluginManager::NoPluginFound& e) {
        std::cerr << e.what() << '\n';
    }


    return 0;
}

```
