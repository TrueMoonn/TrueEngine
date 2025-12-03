project(TE_unit_tests)

########## GOOGLE TESTING ##########
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

########## LINKAGE ##########
add_executable(${PROJECT_NAME}
    DlManager.cpp
    PluginManager.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        TrueEngine
        tomlplusplus::tomlplusplus
        GTest::gtest_main
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
)

########## TESTS ##########
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/tests/unit_tests/plugins
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/plugins/movement.so
        ${CMAKE_SOURCE_DIR}/tests/unit_tests/plugins/movement.so
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/plugins/interaction.so
        ${CMAKE_SOURCE_DIR}/tests/unit_tests/plugins/interaction.so
    COMMAND ${CMAKE_COMMAND} -E echo "67" > ${CMAKE_SOURCE_DIR}/tests/unit_tests/plugins/wrong.so
)
