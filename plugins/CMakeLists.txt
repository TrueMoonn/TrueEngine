project(plugins)

########## PLUGINS ##########
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# MOVEMENT
add_subdirectory(${PROJECT_SOURCE_DIR}/movement)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/movement Movement.hpp
    cp -R ../plugins/movement/include/. ../include
    "
)

# WINDOW
add_subdirectory(${PROJECT_SOURCE_DIR}/window)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/window Window.hpp
    cp -R ../plugins/window/include/. ../include
    "
)