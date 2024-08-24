cmake_minimum_required(VERSION 3.16)
set(CMAKE_BUILD_TYPE Debug)

project(assembler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(functions.cmake)

# if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2)
# elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
#     add_compile_options(/W4)
# endif()

add_executable(assembler
    assembler.cpp
)

add_library(assembler_includes INTERFACE)

add_subdirectory(common)
add_subdirectory(lines)
add_subdirectory(commands)
add_subdirectory(preprocessing)

target_link_libraries(assembler INTERFACE assembler_includes)
