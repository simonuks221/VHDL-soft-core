macro(assembler_add_library name)
#Parse arguemnts
    cmake_parse_arguments(
        PARSED
        "" #Boolean params
        "" #Single params
        "SRC;LIB" #Multiple params (public sources and libs)
        ${ARGN}
    )
    if(DEFINED PARSED_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unparsed arguments from assembler_add_library: ${PARSED_UNPARSED_ARGUMENTS}")
    endif()

    add_library(${name})

    # Add new library path so no #include "/foler/file.hpp" is needed
    target_include_directories(assembler_includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
    # Link library to the main program
    target_link_libraries(assembler PRIVATE ${name})
    #Add sources to library
    target_sources(${name} PRIVATE ${PARSED_SRC})
    target_link_libraries(${name} PUBLIC ${PARSED_LIB})
    target_link_libraries(${name} INTERFACE assembler_includes)
endmacro()
