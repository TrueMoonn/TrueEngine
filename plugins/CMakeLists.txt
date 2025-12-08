project(plugins)

########## PLUGINS ##########
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# SFML
add_subdirectory(${PROJECT_SOURCE_DIR}/sfml)
execute_process(
    COMMAND bash -c "
    rm -rf ../include/sfml ../include/Sfml.hpp
    cp -R ../plugins/sfml/include/. ../include
    "
)

# ENTITY SPEC
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
