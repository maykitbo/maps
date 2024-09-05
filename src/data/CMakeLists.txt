cmake_minimum_required(VERSION 3.5)

project(database_manager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    data_manager/postgis_connector.cc
)

set(HEADERS
    data_manager/postgis_connector.h
    interface.h
)

add_subdirectory(interface database_manager ../shared)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
# Link with libpainters.a library
# target_link_libraries(${PROJECT_NAME} PUBLIC painters)