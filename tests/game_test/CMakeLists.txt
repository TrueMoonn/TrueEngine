cmake_minimum_required(VERSION 3.10)
project(GameTest)

########## SETUP ##########
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(GT_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(GT_HDR_DIR "${PROJECT_SOURCE_DIR}/include")
set(TE_DIR "${PROJECT_SOURCE_DIR}/../..")
set(TE_HDR_DIR "${TE_DIR}/include")

########## LIBRARIES ##########
link_directories(
    ${TE_DIR}
)

########## EXECUTABLE ##########
add_executable( ${PROJECT_NAME}
    ${GT_SRC_DIR}/main.cpp
    ${GT_SRC_DIR}/scenes/InGame.cpp
    # ${GT_SRC_DIR}/scenes/Menu.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${GT_HDR_DIR}
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
            TrueEngine
            SFML::Graphics
            SFML::Systems
            SFML::Window
            SFML::Audio
    )
else ()
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            TrueEngine
            ${SFML_GRAPHICS}
            ${SFML_SYSTEM}
            ${SFML_WINDOW}
            ${SFML_AUDIO}
    )
endif ()
