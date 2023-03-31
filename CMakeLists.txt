cmake_minimum_required(VERSION 3.0.0)

project(QT-library-homework)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_AUTORCC on)

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS ui)

find_package(Qt5 COMPONENTS 
    Widgets
    Gui
    Core
    Sql
)

file(
    GLOB
    SOURCES_FILES
    src/*.cpp
)

file(
    GLOB
    HEADER_FILES
    includes/*.h
)

file(
    GLOB
    UI_FILES
    ui/*.ui
)

file(
    GLOB
    QRC_FILES
    *.qrc
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES_FILES}
    ${HEADER_FILES}
    ${UI_FILES}
    ${QRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    includes
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
)