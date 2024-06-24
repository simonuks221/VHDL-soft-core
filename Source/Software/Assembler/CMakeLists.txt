cmake_minimum_required(VERSION 3.10)
project(assembler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(assembler assembler.cpp)

add_subdirectory(commands)

target_link_libraries(assembler PRIVATE commands)
