cmake_minimum_required(VERSION 3.5)

project(database_lib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/idata)
set(DATA_MANAGER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/database_manager)
set(SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../shared)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

set(TUNE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tune_db)


set(SOURCES
    ${DATA_MANAGER_DIR}/connector.cc
    ${DATA_MANAGER_DIR}/connector.h
    ${DATA_MANAGER_DIR}/queries.h
    ${DATA_MANAGER_DIR}/queries.cc
    ${DATA_MANAGER_DIR}/structure.h
    ${SHARED_DIR}/types.h
    ${SHARED_DIR}/log.h
    ${INTERFACE_DIR}/idata.h
    ${INTERFACE_DIR}/idata.cc
    ${INTERFACE_DIR}/types/line.h
    ${INTERFACE_DIR}/types/polygon.h
    ${INTERFACE_DIR}/features/feature.h
    ${INTERFACE_DIR}/features/set.h

)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${INTERFACE_DIR}
    ${DATA_MANAGER_DIR}
    ${SHARED_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC -lpqxx -lpq)


option(TEST_FLAG "Test define flag" OFF)
option(TUNE_DATABASE "Build the tune database main" OFF)


if(TEST_FLAG)
    set(TEST_SOURCES
        ${TEST_DIR}/main.cc
        ${TEST_DIR}/tests.h
        ${SHARED_DIR}/config.h
        ${SHARED_DIR}/time_test.h

        ${TEST_DIR}/wkb/wkb.h
        ${TEST_DIR}/temp_test/temp_test.h
    )

    add_executable(data_test ${TEST_SOURCES})
    target_link_libraries(data_test PRIVATE ${PROJECT_NAME})

    message(TEST FLAG = ${TEST_FLAG})
    # Use the TEST_FLAG variable to define preprocessor definitions
    if(DEFINED TEST_FLAG)
        target_compile_definitions(data_test PRIVATE ${TEST_FLAG})
    endif()
endif()


if(TUNE_DATABASE)
    set(TUNE_SOURCES
        ${TUNE_DIR}/tune.h
        ${TUNE_DIR}/main.cc
        ${SHARED_DIR}/config.h
        ${SHARED_DIR}/time_test.h
    )

    add_executable(tune_database ${TUNE_SOURCES})
    target_link_libraries(tune_database PRIVATE ${PROJECT_NAME})
endif()
