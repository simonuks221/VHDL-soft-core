add_library(optimisation constant_folding.cpp data_flow_analysis.cpp )

target_include_directories(optimisation PUBLIC ${CMAKE_SOURCE_DIR}/binary_tree)
target_link_libraries(optimisation PRIVATE binary_tree)
