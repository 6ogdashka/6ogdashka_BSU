cmake_minimum_required(VERSION 3.10)
project(MatrixProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    main.cpp
    fraction.cpp
)

set(HEADERS
    russian.h
    fraction.h
)

add_executable(main_program ${SOURCES} ${HEADERS})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(main_program PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic 
        -g
        -Wno-unused-parameter
    )
endif()
