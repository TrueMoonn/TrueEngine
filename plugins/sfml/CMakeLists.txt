project(sfml)

#/ Library \#
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp

    #COMPONENTS
    ${PROJECT_SOURCE_DIR}/src/components/sprite.cpp
    ${PROJECT_SOURCE_DIR}/src/components/window.cpp

    #SYSTEMS
    ${PROJECT_SOURCE_DIR}/src/systems/display.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/draw.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/view_player.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/parallax.cpp

    #EVENTS
    ${PROJECT_SOURCE_DIR}/src/events/pollEvent.cpp
    ${PROJECT_SOURCE_DIR}/src/events/keyboard.cpp
)
add_library(addon::sfml ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${TE_HDR_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        TrueEngine
        tomlplusplus::tomlplusplus
)

if (ENABLE_TE_COVERAGE)
    target_link_libraries(${PROJECT_NAME} PUBLIC gcov)
endif ()
