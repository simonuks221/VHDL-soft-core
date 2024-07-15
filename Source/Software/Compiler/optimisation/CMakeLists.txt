add_library(optimisation constant_folding.cpp data_flow_analysis.cpp)

target_include_directories(optimisation PUBLIC ${CMAKE_SOURCE_DIR}/token)
target_link_libraries(optimisation PRIVATE token)
