project(display)

#/ Library \#
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/display.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/draw.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/view_player.cpp
)
add_library(plugins::display ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${TE_HDR_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ECS
        TrueEngine
)
