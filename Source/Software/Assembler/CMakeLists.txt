cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)

project(assembler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(assembler
    assembler.cpp
)

add_subdirectory(commands)
add_subdirectory(preprocessing)
add_subdirectory(lines)

# So no directory is needed in includes
include_directories(commands)
include_directories(preprocessing)
include_directories(lines)

target_link_libraries(assembler
    PRIVATE
        commands
        preprocessing
        lines
)
