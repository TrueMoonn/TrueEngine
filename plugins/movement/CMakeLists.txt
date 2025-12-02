project(movement)

#/ Library \#
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp
    ${PROJECT_SOURCE_DIR}/src/components/velocity.cpp
    ${PROJECT_SOURCE_DIR}/src/components/position.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/movement.cpp
)
add_library(plugins::movement ALIAS ${PROJECT_NAME})

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
