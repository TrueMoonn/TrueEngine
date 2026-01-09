project(plugins)

########## PLUGINS ##########
if (WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# SFML
add_subdirectory(${PROJECT_SOURCE_DIR}/sfml)
file(REMOVE_RECURSE
    ${PROJECT_SOURCE_DIR}/../include/sfml
    ${PROJECT_SOURCE_DIR}/../include/Sfml.hpp
)
file(COPY ${PROJECT_SOURCE_DIR}/sfml/include/
    DESTINATION ${PROJECT_SOURCE_DIR}/../include)

# DISPLAY
add_subdirectory(${PROJECT_SOURCE_DIR}/display)
file(REMOVE_RECURSE
    ${PROJECT_SOURCE_DIR}/../include/display
    ${PROJECT_SOURCE_DIR}/../include/Display.hpp
)
file(COPY ${PROJECT_SOURCE_DIR}/display/include/
    DESTINATION ${PROJECT_SOURCE_DIR}/../include)

# ENTITY SPEC
add_subdirectory(${PROJECT_SOURCE_DIR}/entity_specs)
file(REMOVE_RECURSE
    ${PROJECT_SOURCE_DIR}/../include/entity_specs
    ${PROJECT_SOURCE_DIR}/../include/EntitySpec.hpp
)
file(COPY ${PROJECT_SOURCE_DIR}/entity_specs/include/
    DESTINATION ${PROJECT_SOURCE_DIR}/../include)

# PHYSIC
add_subdirectory(${PROJECT_SOURCE_DIR}/physic)
file(REMOVE_RECURSE
    ${PROJECT_SOURCE_DIR}/../include/physic
    ${PROJECT_SOURCE_DIR}/../include/Physic.hpp
)
file(COPY ${PROJECT_SOURCE_DIR}/physic/include/
    DESTINATION ${PROJECT_SOURCE_DIR}/../include)

# INTERACTION
add_subdirectory(${PROJECT_SOURCE_DIR}/interaction)
file(REMOVE_RECURSE
    ${PROJECT_SOURCE_DIR}/../include/interaction
    ${PROJECT_SOURCE_DIR}/../include/Interaction.hpp
)
file(COPY ${PROJECT_SOURCE_DIR}/interaction/include/
    DESTINATION ${PROJECT_SOURCE_DIR}/../include)
