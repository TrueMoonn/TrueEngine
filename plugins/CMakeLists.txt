project(plugins)

########## PLUGINS ##########
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# SFML
add_subdirectory(${PROJECT_SOURCE_DIR}/sfml)
if(WIN32)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/../include/sfml
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_SOURCE_DIR}/../include/Sfml.hpp
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sfml/include ${PROJECT_SOURCE_DIR}/../include
    )
else()
    execute_process(
        COMMAND bash -c "
        rm -rf ${PROJECT_SOURCE_DIR}/../include/sfml ${PROJECT_SOURCE_DIR}/../include/Sfml.hpp
        cp -R ${PROJECT_SOURCE_DIR}/sfml/include/. ${PROJECT_SOURCE_DIR}/../include
        "
    )
endif()

# DISPLAY
add_subdirectory(${PROJECT_SOURCE_DIR}/display)
if(WIN32)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/../include/display
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_SOURCE_DIR}/../include/Display.hpp
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/display/include ${PROJECT_SOURCE_DIR}/../include
    )
else()
    execute_process(
        COMMAND bash -c "
        rm -rf ${PROJECT_SOURCE_DIR}/../include/display ${PROJECT_SOURCE_DIR}/../include/Display.hpp
        cp -R ${PROJECT_SOURCE_DIR}/display/include/. ${PROJECT_SOURCE_DIR}/../include
        "
    )
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/physic)
if(WIN32)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/../include/physic
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_SOURCE_DIR}/../include/Physic.hpp
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/physic/include ${PROJECT_SOURCE_DIR}/../include
    )
else()
    execute_process(
        COMMAND bash -c "
        rm -rf ${PROJECT_SOURCE_DIR}/../include/physic ${PROJECT_SOURCE_DIR}/../include/Physic.hpp
        cp -R ${PROJECT_SOURCE_DIR}/physic/include/. ${PROJECT_SOURCE_DIR}/../include
        "
    )
endif()

# ENTITY SPEC
add_subdirectory(${PROJECT_SOURCE_DIR}/entity_specs)
if(WIN32)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/../include/entity_spec
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_SOURCE_DIR}/../include/EntitySpec.hpp
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/entity_specs/include ${PROJECT_SOURCE_DIR}/../include
    )
else()
    execute_process(
        COMMAND bash -c "
        rm -rf ${PROJECT_SOURCE_DIR}/../include/entity_spec ${PROJECT_SOURCE_DIR}/../include/EntitySpec.hpp
        cp -R ${PROJECT_SOURCE_DIR}/entity_specs/include/. ${PROJECT_SOURCE_DIR}/../include
        "
    )
endif()

# INTERACTION
add_subdirectory(${PROJECT_SOURCE_DIR}/interaction)
if(WIN32)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/../include/interaction
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_SOURCE_DIR}/../include/Interaction.hpp
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/interaction/include ${PROJECT_SOURCE_DIR}/../include
    )
else()
    execute_process(
        COMMAND bash -c "
        rm -rf ${PROJECT_SOURCE_DIR}/../include/interaction ${PROJECT_SOURCE_DIR}/../include/Interaction.hpp
        cp -R ${PROJECT_SOURCE_DIR}/interaction/include/. ${PROJECT_SOURCE_DIR}/../include
        "
    )
endif()
