add_library(preprocessing
    preprocessor.cpp
)

target_include_directories(preprocessing
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lines
        ${CMAKE_SOURCE_DIR}/commands
)

target_link_libraries(preprocessing
    PRIVATE
        lines
        commands
)