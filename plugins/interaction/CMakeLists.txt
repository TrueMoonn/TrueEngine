project(interaction)

########## LIBRARY ##########
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp
    ${PROJECT_SOURCE_DIR}/src/components/interactive.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/interaction.cpp
)
add_library(plugins::interaction ALIAS ${PROJECT_NAME})

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
