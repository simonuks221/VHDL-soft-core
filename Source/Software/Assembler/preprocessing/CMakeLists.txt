add_library(preprocessing
    preprocessor.cpp
)

target_include_directories(preprocessing
    PUBLIC
        ${CMAKE_SOURCE_DIR}/lines
)

target_link_libraries(preprocessing
    PRIVATE
        lines
)