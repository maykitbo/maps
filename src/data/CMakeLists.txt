cmake_minimum_required(VERSION 3.5)

project(data_manager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)
set(DATA_STRUCTURE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/geojson_handler)
set(DATA_MANAGER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/database_manager)
set(SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../shared)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    ${DATA_MANAGER_DIR}/postgis_connector.cc
    ${INTERFACE_DIR}/idata.cc
    ${DATA_STRUCTURE_DIR}/geojson_handler.cc
)

set(HEADERS
    ${DATA_MANAGER_DIR}/postgis_connector.h
    ${DATA_MANAGER_DIR}/queries.h
    ${INTERFACE_DIR}/idata.h
    ${SHARED_DIR}/types.h
    ${SHARED_DIR}/config.h
    ${DATA_STRUCTURE_DIR}/geojson_handler.h
)

set(TEST_SOURCES
    ${TEST_DIR}/test.cc
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${INTERFACE_DIR}
    ${DATA_STRUCTURE_DIR}
    ${DATA_MANAGER_DIR}
    ${SHARED_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC -lpqxx -lpq)

# Option to build tests
option(BUILD_TESTS "Build the tests" OFF)

if(BUILD_TESTS)
    add_executable(test_database_manager ${TEST_SOURCES})
    target_link_libraries(test_database_manager PRIVATE ${PROJECT_NAME})
endif()
