cmake_minimum_required(VERSION 3.5)

project(maykitbo_maps VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(DB_LIB_PATH CACHE PATH "Path to the database library")

set(HEADERS
    mainwindow.h
)

set(SOURCES
    main.cc
    mainwindow.cc
)

set(UI

)

set(RESOURCES

)

add_subdirectory(${DB_LIB_PATH} ${CMAKE_BINARY_DIR}/database_lib_build)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${UI})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets database_lib)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()