project(entity_spec)

########## LIBRARY ##########
add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/factory.cpp
    ${PROJECT_SOURCE_DIR}/src/components/damage.cpp
    ${PROJECT_SOURCE_DIR}/src/components/health.cpp
    ${PROJECT_SOURCE_DIR}/src/systems/deal_damage.cpp
)
add_library(plugins::entity_spec ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${TE_HDR_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        TrueEngine
)
