project(plugins)

########## PLUGINS ##########
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# MOVEMENT
add_subdirectory(${PROJECT_SOURCE_DIR}/movement)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/movement ../include/Movement.hpp
    cp -R ../plugins/movement/include/. ../include
    "
)

# WINDOW
add_subdirectory(${PROJECT_SOURCE_DIR}/display)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/display ../include/Display.hpp
    cp -R ../plugins/display/include/. ../include
    "
)

# WINDOW
add_subdirectory(${PROJECT_SOURCE_DIR}/entity_specs)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/entity_spec ../include/EntitySpec.hpp
    cp -R ../plugins/entity_specs/include/. ../include
    "
)

# PHYSIC
add_subdirectory(${PROJECT_SOURCE_DIR}/physic)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/physic ../include/Physic.hpp
    cp -R ../plugins/physic/include/. ../include
    "
)

# INTERACTION
add_subdirectory(${PROJECT_SOURCE_DIR}/interaction)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/interaction ../include/Interaction.hpp
    cp -R ../plugins/interaction/include/. ../include
    "
)
