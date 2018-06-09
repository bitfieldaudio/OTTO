set(OTTO_OPTIONS "")

# Declare an option which will prefixed with OTTO_, and #defined as 1 or 0
function(otto_option NAME DESC)
    if(${ARGN})
       	option("OTTO_${NAME}" "${DESC}" ON)
    else()
       	option("OTTO_${NAME}" "${DESC}" OFF)
    endif()
	
    list(APPEND OTTO_OPTIONS "${NAME}")
    set(OTTO_OPTIONS "${OTTO_OPTIONS}" PARENT_SCOPE)
endfunction(otto_option)


# Add defintions to target
function(otto_add_definitions TARGET)
    foreach(item IN LISTS OTTO_OPTIONS)
        if(${OTTO_${item}})
            target_compile_definitions(${TARGET} PUBLIC "OTTO_${item}=1")
        else()
            target_compile_definitions(${TARGET} PUBLIC "OTTO_${item}=0")
        endif()
    endforeach(item)
endfunction(otto_add_definitions)

# Echo all definitions
function(otto_debug_definitions)
    message("\nOTTO Build Configuration:")
    foreach(item IN LISTS OTTO_OPTIONS)
        if(OTTO_${item})
            message("   YES | ${item}")
        else()
            message("    NO | ${item}")
        endif()
    endforeach(item)
    message("\n")
endfunction(otto_debug_definitions)

macro(otto_include_board BOARD)

    set(BOARD_DIR "${OTTO_SOURCE_DIR}/boards/${BOARD}/")

    if(NOT IS_DIRECTORY ${BOARD_DIR})
      message(FATAL_ERROR "Invalid board '${BOARD}'")
    endif()
    
    string(REPLACE "/" "_" BOARD_DEFINITION_NAME ${BOARD})
    string(REPLACE "-" "_" BOARD_DEFINITION_NAME ${BOARD_DEFINITION_NAME})
    string(TOUPPER "${BOARD_DEFINITON_NAME}" BOARD_DEFINITION_NAME)
    target_compile_definitions(otto PUBLIC "OTTO_BOARD_${BOARD_DEFINITION_NAME}")
    target_include_directories(otto PUBLIC ${BOARD_DIR}/include)
    
    file(GLOB_RECURSE BOARD_SOURCES ${BOARD_DIR}/src/*.cpp)
    if (NOT "${BOARD_SOURCES}" STREQUAL "") 
        target_sources(otto PRIVATE ${BOARD_SOURCES})
    endif()

    include(${BOARD_DIR}/config.cmake)

endmacro(otto_include_board)
