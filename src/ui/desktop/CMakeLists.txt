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
set(CORE_LIB_PATH CACHE PATH "Path to the core library")


set(HEADERS
    mainwindow/mainwindow.h
    drawing/scene/scene.h
    drawing/render/render.h
    drawing/dataloader/dataloader.h
    drawing/sceneset/sceneset.h
    drawing/mapitems/mapitems.h
    drawing/style/map_style.h
    drawing/style/lod.h
)

set(SOURCES
    main.cc
    mainwindow/mainwindow.cc
    drawing/scene/scene.cc
    drawing/render/render.cc
    drawing/dataloader/dataloader.cc
    drawing/scene/connect.cc
    drawing/sceneset/sceneset.cc
    drawing/mapitems/mapitems.cc
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
    drawing
    drawing/scene
    drawing/render
    drawing/sceneset
    drawing/dataloader
    drawing/mapitems
    mainwindow
    drawing/style
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()