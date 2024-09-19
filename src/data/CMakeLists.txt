cmake_minimum_required(VERSION 3.5)

project(database_lib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)
# set(DATA_STRUCTURE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/geojson_handler)
set(DATA_MANAGER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/database_manager)
set(SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../shared)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TUNE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tune_db)

# set(SOURCES
#     # ${INTERFACE_DIR}/idata.cc
#     # ${DATA_STRUCTURE_DIR}/geojson_handler.cc
# )

set(SOURCES
    ${DATA_MANAGER_DIR}/postgis_connector.cc
    ${DATA_MANAGER_DIR}/postgis_connector.h
    ${DATA_MANAGER_DIR}/queries.h
    # ${INTERFACE_DIR}/idata.h
    ${SHARED_DIR}/types.h
    ${SHARED_DIR}/config.h
    ${SHARED_DIR}/log.h
    # ${DATA_STRUCTURE_DIR}/geojson_handler.h
    ${INTERFACE_DIR}/polygon_types.h
    ${INTERFACE_DIR}/draw_polygon_data.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${INTERFACE_DIR}
    # ${DATA_STRUCTURE_DIR}
    ${DATA_MANAGER_DIR}
    ${SHARED_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC -lpqxx -lpq)


option(BUILD_TESTS "Build the tests" OFF)
option(TUNE_DATABASE "Build the tune database main" OFF)


if(BUILD_TESTS)
    set(TEST_SOURCES
        ${TEST_DIR}/test.cc
    )

    add_executable(test_database_lib ${TEST_SOURCES})
    target_link_libraries(test_database_lib PRIVATE ${PROJECT_NAME})
endif()


if(TUNE_DATABASE)
    set(TUNE_SOURCES
        ${TUNE_DIR}/tune.h
        ${TUNE_DIR}/main.cc
    )

    add_executable(tune_database ${TUNE_SOURCES})
    target_link_libraries(tune_database PRIVATE ${PROJECT_NAME})
endif()
