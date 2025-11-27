project(physic)

########## LIBRARY ##########
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp
    ${PROJECT_SOURCE_DIR}/src/components/hitbox.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/hitbox.cpp
    ${PROJECT_SOURCE_DIR}/src/hitbox_management.cpp
)
add_library(plugins::physic ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${TE_HDR_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ECS
)
