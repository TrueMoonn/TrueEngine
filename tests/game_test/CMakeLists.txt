cmake_minimum_required(VERSION 3.10)
project(GameTest)

########## SETUP ##########
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(GT_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(GT_HDR_DIR "${PROJECT_SOURCE_DIR}/include")
set(TE_DIR "${PROJECT_SOURCE_DIR}/../..")
set(TE_HDR_DIR "${TE_DIR}/include")

########## LIBRARIES ##########
link_directories(
    ${TE_DIR}
)

########## EXECUTABLE ##########
add_executable( ${PROJECT_NAME}
    ${GT_SRC_DIR}/main.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${GT_HDR_DIR}
        ${TE_HDR_DIR}
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        TrueEngine
)
