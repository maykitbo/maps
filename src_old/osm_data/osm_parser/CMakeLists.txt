cmake_minimum_required(VERSION 3.5)

project(osm_parser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    parser.cc
)

set(HEADERS
    parser.h
    config.h
)

# Add the painters subdirectory
# add_subdirectory(painters)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
# Link with libpainters.a library
# target_link_libraries(${PROJECT_NAME} PUBLIC painters)