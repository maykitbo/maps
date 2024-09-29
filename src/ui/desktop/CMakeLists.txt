cmake_minimum_required(VERSION 3.5)

project(maykitbo_maps VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Concurrent REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent REQUIRED)

set(DB_LIB_PATH CACHE PATH "Path to the database library")
set(CORE_LIB_PATH CACHE PATH "Path to the database library")

set(SCENE_DIR scene)
set(MAINWINDOW_DIR mainwindow)
set(STYLE_DIR style)

set(HEADERS
    ${MAINWINDOW_DIR}/mainwindow.h
    ${SCENE_DIR}/scene.h
    ${SCENE_DIR}/sceneset.h
    ${SCENE_DIR}/mapitems.h
    ${STYLE_DIR}/map_style.h
    ${STYLE_DIR}/lod.h
)

set(SOURCES
    main.cc
    ${MAINWINDOW_DIR}/mainwindow.cc
    ${SCENE_DIR}/scene.cc
    ${SCENE_DIR}/sceneset.cc
    # ${SCENE_DIR}/mapitems.cc
)

set(UI

)

set(RESOURCES

)

add_subdirectory(${DB_LIB_PATH} ${CMAKE_BINARY_DIR}/database_lib_build)
add_subdirectory(${CORE_LIB_PATH} ${CMAKE_BINARY_DIR}/core_lib_build)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${UI})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
    database_lib
    core_lib
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${SCENE_DIR}
    ${MAINWINDOW_DIR}
    ${STYLE_DIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()