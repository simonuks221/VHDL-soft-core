add_library(optimisation STATIC constant_folding.cpp data_flow_analysis.cpp)

target_include_directories(optimisation PUBLIC ${CMAKE_SOURCE_DIR}/token)

add_subdirectory(binary_tree)

target_link_libraries(optimisation PRIVATE token binary_tree)
