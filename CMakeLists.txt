cmake_minimum_required(VERSION 3.10)
project(TrueEngine)

########## SETUP ##########
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(TE_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TE_HDR_DIR "${PROJECT_SOURCE_DIR}/include")

########## HEADER UPDATE ##########
message("Updating project header from ECS and Network...")
execute_process (
    COMMAND bash -c "
        rm -rf ../include/ECS && rm -rf ../include/Network
        mkdir ../include/ECS && mkdir ../include/Network
        cp -R ../ECS/include/. ../include/ECS/
        cp -R ../Network/include/. ../include/Network
    "
)
message("Updating project header from ECS and Network... DONE")

########## OPTIONS ##########
option(ENABLE_TE_TESTS "Build tests along with the library" OFF)
option(ENABLE_TE_COVERAGE "Enable coverage reporting" OFF)

########## UNIT TESTS ##########
if(ENABLE_TE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()
endif()

if (ENABLE_TE_TESTS)
  enable_testing()
  add_subdirectory(tests/unit_tests)
endif ()

########## LIBS ##########
add_subdirectory(ECS)
add_subdirectory(Network)

########## TRUE ENGINE ##########
add_library( ${PROJECT_NAME} STATIC
    $<TARGET_OBJECTS:ECS>
    $<TARGET_OBJECTS:Network>

    # OTHERS
    ${TE_SRC_DIR}/hitbox_management.cpp

    # COMPONENTS
    ${TE_SRC_DIR}/components/clock.cpp
    ${TE_SRC_DIR}/components/hitbox.cpp
    ${TE_SRC_DIR}/components/interactive.cpp
    ${TE_SRC_DIR}/components/position.cpp
    ${TE_SRC_DIR}/components/velocity.cpp
    ${TE_SRC_DIR}/components/window.cpp

    # SYSTEMS
    ${TE_SRC_DIR}/systems/display.cpp
    ${TE_SRC_DIR}/systems/draw.cpp
    ${TE_SRC_DIR}/systems/event.cpp
    ${TE_SRC_DIR}/systems/hitbox.cpp
    ${TE_SRC_DIR}/systems/map.cpp
    ${TE_SRC_DIR}/systems/movement.cpp
    ${TE_SRC_DIR}/systems/view_player.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${TE_HDR_DIR}
)

########## SFML ##########
find_library(SFML_GRAPHICS libsfml-graphics.so.3.0.2)
find_library(SFML_SYSTEM libsfml-system.so.3.0.2)
find_library(SFML_WINDOW libsfml-window.so.3.0.2)
find_library(SFML_AUDIO libsfml-audio.so.3.0.2)

if (${SFML_GRAPHICS} STREQUAL "SFML_GRAPHICS-NOTFOUND" OR
    ${SFML_SYSTEM} STREQUAL "SFML_SYSTEM-NOTFOUND" OR
    ${SFML_AUDIO} STREQUAL "SFML_AUDIO-NOTFOUND" OR
    ${SFML_WINDOW} STREQUAL "SFML_WINDOW-NOTFOUND")
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            ECS
            Network
            SFML::Graphics
            SFML::Systems
            SFML::Window
            SFML::Audio
    )
else ()
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            ECS
            Network
            ${SFML_GRAPHICS}
            ${SFML_SYSTEM}
            ${SFML_WINDOW}
            ${SFML_AUDIO}
    )
endif ()
