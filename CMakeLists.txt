cmake_minimum_required(VERSION 3.10)
project(TrueEngine)

########## SETUP ##########
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -O3")
set(TE_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TE_HDR_DIR "${PROJECT_SOURCE_DIR}/include")
include(FetchContent)

########## HEADER UPDATE ##########
message("\nUpdating project header from ECS and Network...")
execute_process (
    COMMAND bash -c "
        rm -rf ../include/ECS && rm -rf ../include/Network
        cp -R ../ECS/include/. ../include/
        cp -R ../Network/include/. ../include/
    "
)
message("Updating project header from ECS and Network... DONE\n")

########## OPTIONS ##########
option(ENABLE_TE_TESTS "Build tests along with the library" OFF)
option(ENABLE_TE_COVERAGE "Enable coverage reporting" OFF)

########## COVERAGE ##########
if (ENABLE_TE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage -lgcov")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()
endif()

########## LIBS ##########
add_subdirectory(ECS)
add_subdirectory(Network)

########## PLUGINS ##########
add_subdirectory(plugins)

########## TRUE ENGINE ##########
add_library( ${PROJECT_NAME} STATIC
    $<TARGET_OBJECTS:ECS>
    $<TARGET_OBJECTS:Network>

    #PLUGIN
    ${TE_SRC_DIR}/plugin/APlugin.cpp
    ${TE_SRC_DIR}/plugin/DlManager.cpp
    ${TE_SRC_DIR}/plugin/PluginManager.cpp

    # SYSTEM OBJECTS
    ${TE_SRC_DIR}/clock.cpp

    # CONFIG
    ${TE_SRC_DIR}/config/map_loader.cpp

    # GAME TOOL
    ${TE_SRC_DIR}/GameTool.cpp

    # NETWORK INTEGRATION
    ${TE_SRC_DIR}/network/GameClient.cpp
    ${TE_SRC_DIR}/network/GameServer.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${TE_HDR_DIR}
)

########## TOML++ ##########
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        tomlplusplus::tomlplusplus
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
            SFML::System
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

########## TESTS ##########
if (ENABLE_TE_TESTS)
  enable_testing()
  add_subdirectory(tests/unit_tests)
endif ()
