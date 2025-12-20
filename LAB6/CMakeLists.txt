cmake_minimum_required(VERSION 3.10)
project(LibraryProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    Simple_Matrix.cpp
    Solve.cpp
)

set(HEADERS
    Simple_Matrix.h
    russian.h
)

add_executable(main_program ${SOURCES} ${HEADERS})

set(TXT_FILES
    char_matrix.txt
    double_matrix.txt
    int_matrix.txt
)

file(COPY ${TXT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(main_program PRIVATE -Wall -Wextra -Wpedantic -g)
endif()

target_include_directories(main_program PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})