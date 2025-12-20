cmake_minimum_required(VERSION 3.10)
project(MatrixProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    task_2.cpp
)

set(HEADERS
    russian.h
)

add_executable(main_program ${SOURCES} ${HEADERS})

set(TXT_FILES
    Students.txt
)

file(COPY ${TXT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(main_program PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic 
        -g
        -Wno-unused-parameter
    )
endif()
