project(entity_spec)

########## LIBRARY ##########
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp
    ${PROJECT_SOURCE_DIR}/src/components/fragile.cpp
    ${PROJECT_SOURCE_DIR}/src/components/damage.cpp
    ${PROJECT_SOURCE_DIR}/src/components/health.cpp
    ${PROJECT_SOURCE_DIR}/src/components/team.cpp
    ${PROJECT_SOURCE_DIR}/src/components/timeout.cpp
    ${PROJECT_SOURCE_DIR}/src/components/pattern.cpp
)
add_library(addon::entity_spec ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${TE_HDR_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        TrueEngine
        tomlplusplus::tomlplusplus
        addon::physic
)

target_compile_definitions(${PROJECT_NAME} PRIVATE BUILDING_PLUGIN)

if (ENABLE_TE_COVERAGE)
    target_link_libraries(${PROJECT_NAME} PUBLIC gcov)
endif ()
