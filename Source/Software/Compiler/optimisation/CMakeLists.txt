#find_library(SUBDIR1_LIB Subdir1Lib PATHS ${CMAKE_BINARY_DIR}/subdir1)

add_library(optimisation constant_folding.cpp)

target_include_directories(optimisation PUBLIC ${CMAKE_SOURCE_DIR}/binary_tree)
target_link_libraries(optimisation PRIVATE binary_tree)
