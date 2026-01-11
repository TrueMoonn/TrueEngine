project(sfml)

#/ Library \#
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp

    #COMPONENTS
    ${PROJECT_SOURCE_DIR}/src/components/sprite.cpp
    ${PROJECT_SOURCE_DIR}/src/components/window.cpp
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

target_compile_definitions(${PROJECT_NAME} PRIVATE BUILDING_PLUGIN)

if (ENABLE_TE_COVERAGE)
    target_link_libraries(${PROJECT_NAME} PUBLIC gcov)
endif ()
