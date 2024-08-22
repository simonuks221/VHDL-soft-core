cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)

project(assembler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2)
# elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
#     add_compile_options(/W4)
# endif()

add_executable(assembler
    assembler.cpp
)

add_subdirectory(commands)
add_subdirectory(preprocessing)
add_subdirectory(lines)
add_subdirectory(common)

# So no directory is needed in includes
include_directories(commands)
include_directories(preprocessing)
include_directories(lines)
include_directories(common)

target_link_libraries(assembler
    PRIVATE
        commands
        preprocessing
        lines
        common
)
