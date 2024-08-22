add_library(commands
    command_base.cpp
    command_interface.hpp
    command_parser.cpp
    commands.cpp
)

target_include_directories(commands
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lines
        ${CMAKE_SOURCE_DIR}/common
)

target_link_libraries(commands
    PRIVATE
        lines
        common
)