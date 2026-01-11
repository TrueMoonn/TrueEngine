project(physic)

########## LIBRARY ##########
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp

    #COMPONENTS
    ${PROJECT_SOURCE_DIR}/src/components/hitbox.cpp
    ${PROJECT_SOURCE_DIR}/src/components/position.cpp
    ${PROJECT_SOURCE_DIR}/src/components/velocity.cpp

    ${PROJECT_SOURCE_DIR}/src/hitbox_management.cpp
)
add_library(addon::physic ALIAS ${PROJECT_NAME})

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
