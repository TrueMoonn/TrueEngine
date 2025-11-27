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
add_subdirectory(${PROJECT_SOURCE_DIR}/display)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/display Display.hpp
    cp -R ../plugins/display/include/. ../include
    "
)

# PHYSIC
add_subdirectory(${PROJECT_SOURCE_DIR}/physic)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/physic Physic.hpp
    cp -R ../plugins/physic/include/. ../include
    "
)
