cmake_minimum_required(VERSION 3.10)
project(TrueEngine)

########## SETUP ##########
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(TE_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TE_HDR_DIR "${PROJECT_SOURCE_DIR}/include")
set(ECS_HDR_DIR "${PROJECT_SOURCE_DIR}/ECS/include")
set(NET_HDR_DIR "${PROJECT_SOURCE_DIR}/Network/include")

########## OPTIONS ##########
option(ENABLE_TE_TESTS "Build tests along with the library" OFF)
option(ENABLE_TE_COVERAGE "Enable coverage reporting" OFF)

########## TESTING ##########
if(ENABLE_TE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()
endif()

if (ENABLE_TE_TESTS)
  enable_testing()
  add_subdirectory(tests/unit_tests)
endif ()

########## LIBS ##########
add_subdirectory(ECS)
# add_subdirectory(Network)

########## TRUE ENGINE ##########
add_library( ${PROJECT_NAME} STATIC
    ${TE_SRC_DIR}/temp.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${TE_HDR_DIR}
        ${ECS_HDR_DIR}
        # ${NET_HDR_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ECS
)
