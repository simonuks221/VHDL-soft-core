add_library(binary_tree
    binary_tree.cpp
)

target_include_directories(binary_tree
    PUBLIC
        ${CMAKE_SOURCE_DIR}/token
)

target_link_libraries(binary_tree
    PRIVATE
        token
)
