add_library(resolvers cycles_resolver.cpp)

target_include_directories(resolvers PUBLIC ${CMAKE_SOURCE_DIR}/token)

target_link_libraries(resolvers PRIVATE token)