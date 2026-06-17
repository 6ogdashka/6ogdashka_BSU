cmake_minimum_required(VERSION 3.16)

project(StatusBarExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(StatusBarExample
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

target_link_libraries(StatusBarExample PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)