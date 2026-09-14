cmake_minimum_required(VERSION 3.10)
project(lab1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Creator Creator.cpp employee.h)
set_target_properties(Creator PROPERTIES OUTPUT_NAME "Creator.out" SUFFIX "")

add_executable(Reporter Reporter.cpp employee.h)
set_target_properties(Reporter PROPERTIES OUTPUT_NAME "Reporter.out" SUFFIX "")

add_executable(Main Main.cpp employee.h)

add_dependencies(Main Creator Reporter)