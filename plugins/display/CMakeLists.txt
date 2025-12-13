project(display)

#/ Library \#
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp

    #COMPONENTS
    ${PROJECT_SOURCE_DIR}/src/components/animation.cpp
    ${PROJECT_SOURCE_DIR}/src/components/paralax.cpp

    #SYSTEMS
    ${PROJECT_SOURCE_DIR}/src/systems/animate.cpp
)
add_library(addon::display ALIAS ${PROJECT_NAME})

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
