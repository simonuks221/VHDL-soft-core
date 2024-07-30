add_library(token
        token.cpp
        operators.cpp
        tokenizer.cpp
        assembly.cpp
        line.cpp
        keywords.cpp
)

target_include_directories(token
    PUBLIC
        ${CMAKE_SOURCE_DIR}/logging
)

target_link_libraries(token
    PRIVATE
        logging
)
