 # Short Examples

 ## Main

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
