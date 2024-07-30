project(Resolvers)

add_library(resolvers
    cycles_resolver.cpp
    variables_resolver.cpp
)

target_include_directories(resolvers
    PUBLIC
        ${CMAKE_SOURCE_DIR}/token
        ${CMAKE_SOURCE_DIR}/logging
)

target_link_libraries(resolvers
    PRIVATE
        token
        logging
)
