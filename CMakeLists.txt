cmake_minimum_required(VERSION 3.5)

project(QtHtmlEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS
    Core
    Widgets
    WebEngineWidgets REQIURED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::WebEngineCore
    Qt5::WebEngineWidgets)
