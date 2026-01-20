# TrueEngine

**TrueEngine** is a modular C++ game engine designed to support real-time multiplayer games.
It provides core systems such as an **Entity-Component-System (ECS)**, **networking**, **plugin management**, and **game utilities**, and is used as the foundation for projects like **TekLeague**.

---

## Features

* Modern C++23 codebase
* Entity-Component-System (ECS) architecture
* Client / Server networking layer
* Plugin-based engine extensions (shared libraries)
* Cross-platform support (Linux / Windows)
* SFML integration for graphics, audio, and input
* Config system using TOML
* Optional unit tests and coverage reports

---

## Project Structure

* `src/` – Engine source code
* `include/` – Public engine headers
* `ECS/` – Entity-Component-System core
* `Network/` – Networking and protocol system
* `plugins/` – Engine plugins (physics, display, interaction, etc.)
* `tests/` – Unit tests and game tests
* `build/` – Build directory (generated)

---

## Build Instructions

The project uses **CMake** and a helper build script.

### Build the engine

```bash
./build.sh --build
```

### Rebuild from scratch

```bash
./build.sh --re-build
```

### Debug build

```bash
./build.sh --debug-build
```

### Clean generated files

```bash
./build.sh --clear
```

---

## Tests & Coverage

### Build and run unit tests with coverage

```bash
./build.sh --build-tests
```

This generates an HTML coverage report.

---

## Documentation

Generate local documentation using **Doxygen**:

```bash
./build.sh --doxygen
```

---

## Plugins

TrueEngine supports dynamic plugins compiled as shared libraries:

* Physics
* Display
* Interaction
* Entity specifications
* SFML integration

Plugins are automatically built and copied during compilation.

---

## Usage

TrueEngine is intended to be used as a **library** and linked to game projects.
It handles low-level engine systems, while game logic remains in the game project.

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
    gtool.createSystem("poll_event");
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

    // Create a signal subscription to close the project
    bool running = true;
    gtool.sub("closed", [&running](){
        running = false;
    });
    # The system "poll_event" will emit "closed" event when you quit the window

    /* Main loop */
    while (running) {
        // Run systems loaded
        gtool.runSystems();
    }
    return 0;
}

---
