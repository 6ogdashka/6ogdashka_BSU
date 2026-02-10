cmake_minimum_required(VERSION 3.10)
project(LibraryProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main_program
    Library.cpp
    main.cpp
)

configure_file(
    Books.txt
    ${CMAKE_CURRENT_BINARY_DIR}/Books.txt
    COPYONLY
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(main_program PRIVATE -Wall -Wextra -Wpedantic -g)
endif()

target_include_directories(main_program PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})