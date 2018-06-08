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
