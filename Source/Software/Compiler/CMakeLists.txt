cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)

project(compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(compiler compiler.cpp)

add_subdirectory(optimisation)
add_subdirectory(token)
add_subdirectory(resolvers)
add_subdirectory(logging)

include_directories(logging)
include_directories(token)

target_link_libraries(compiler
    PRIVATE
        optimisation
        binary_tree
        token
        resolvers
        logging
)
