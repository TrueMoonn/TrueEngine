project(plugins)

########## PLUGINS ##########
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# SFML
add_subdirectory(${PROJECT_SOURCE_DIR}/sfml)
execute_process(
    COMMAND bash -c "
    rm -rf ${PROJECT_SOURCE_DIR}/../include/sfml ${PROJECT_SOURCE_DIR}/../include/Sfml.hpp
    cp -R ${PROJECT_SOURCE_DIR}/sfml/include/. ${PROJECT_SOURCE_DIR}/../include
    "
)

# # DISPLAY
# add_subdirectory(${PROJECT_SOURCE_DIR}/display)
# execute_process(
#     COMMAND bash -c "
#     rm -rf ${PROJECT_SOURCE_DIR}/../include/display ${PROJECT_SOURCE_DIR}/../include/Display.hpp
#     cp -R ${PROJECT_SOURCE_DIR}/display/include/. ${PROJECT_SOURCE_DIR}/../include
#     "
# )

# ENTITY SPEC
add_subdirectory(${PROJECT_SOURCE_DIR}/entity_specs)
execute_process(
    COMMAND bash -c "
    rm -rf ${PROJECT_SOURCE_DIR}/../include/entity_spec ${PROJECT_SOURCE_DIR}/../include/EntitySpec.hpp
    cp -R ${PROJECT_SOURCE_DIR}/entity_specs/include/. ${PROJECT_SOURCE_DIR}/../include
    "
)

# PHYSIC
add_subdirectory(${PROJECT_SOURCE_DIR}/physic)
execute_process(
    COMMAND bash -c "
    rm -rf ${PROJECT_SOURCE_DIR}/../include/physic ${PROJECT_SOURCE_DIR}/../include/Physic.hpp
    cp -R ${PROJECT_SOURCE_DIR}/physic/include/. ${PROJECT_SOURCE_DIR}/../include
    "
)

# INTERACTION
add_subdirectory(${PROJECT_SOURCE_DIR}/interaction)
execute_process(
    COMMAND bash -c "
    rm -rf ${PROJECT_SOURCE_DIR}/../include/interaction ${PROJECT_SOURCE_DIR}/../include/Interaction.hpp
    cp -R ${PROJECT_SOURCE_DIR}/interaction/include/. ${PROJECT_SOURCE_DIR}/../include
    "
)
