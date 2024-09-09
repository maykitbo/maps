cmake_minimum_required(VERSION 3.5)

project(core_lib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)
set(GCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gcs)
set(SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../shared)
# set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    ${GCS_DIR}/gcs.cc
)

set(HEADERS
    ${GCS_DIR}/gcs.h
    ${SHARED_DIR}/types.h
)

# set(TEST_SOURCES
#     ${TEST_DIR}/test.cc
# )

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
    # ${INTERFACE_DIR}
    ${GCS_DIR}
    ${SHARED_DIR}
)

# Option to build tests
option(BUILD_TESTS "Build the tests" OFF)

# if(BUILD_TESTS)
#     add_executable(test_database_lib ${TEST_SOURCES})
#     target_link_libraries(test_database_lib PRIVATE ${PROJECT_NAME})
# endif()
