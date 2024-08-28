cmake_minimum_required(VERSION 3.5)

project(maps VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(HEADERS
    mainwindow.h
)

set(SOURCES
    main.cc
    mainwindow.cc
)

set(UI
    mainwindow.ui
)

set(RESOURCES
)

add_subdirectory(osm_parser)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${UI})

# target_link_libraries(${PROJECT_NAME} PRIVATE osm_parser)

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(${PROJECT_NAME}
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
# else()
#     add_executable(${PROJECT_NAME}
#         ${PROJECT_SOURCES}
#     )
# endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets osm_parser)

# set_target_properties(${PROJECT_NAME} PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
