function(ocpppp_generate TARGET_NAME WORKING_DIRECTORY SOURCE_FILE INPUT_FILES) 
  set(OCPPPP_GENERATED_FILES "")
  set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/${TARGET_NAME}_ocpppp")
  foreach(file IN LISTS INPUT_FILES)
    string(REGEX REPLACE "^(.*)\\.([^.]+)$" "\\1.gen.\\2" OUT_FILE "${OUTPUT_DIR}/${file}")
    execute_process(
      COMMAND "${OTTO_SOURCE_DIR}/scripts/detect-gen-dependencies.sh" "${WORKING_DIRECTORY}" "${file}" "${OUTPUT_DIR}"
      OUTPUT_VARIABLE EXTRA_DEPENDENCIES
      RESULT_VARIABLE SHOULD_GEN
    )
    if(SHOULD_GEN EQUAL 0)
      add_custom_command(OUTPUT "${OUT_FILE}"
        COMMAND "${OTTO_SOURCE_DIR}/scripts/ensure-parent-dirs.sh" "${OUT_FILE}"
        COMMAND ocpppp "${WORKING_DIRECTORY}/${file}"  "${OUT_FILE}" --database_dir "${OTTO_BINARY_DIR}" --database_file "${SOURCE_FILE}" --std c++20  
        COMMAND "clang-format" "-i" "${OUT_FILE}"
        DEPENDS ${EXTRA_DEPENDENCIES} "${WORKING_DIRECTORY}/${file}" "${OTTO_BINARY_DIR}/compile_commands.json"
        COMMAND_EXPAND_LISTS
      )
      list(APPEND OCPPPP_GENERATED_FILES "${OUT_FILE}")
    endif()
  endforeach()
  target_include_directories(${TARGET_NAME} PUBLIC "${OUTPUT_DIR}")

  add_custom_target(ocpppp_${TARGET_NAME}_headers ALL DEPENDS "${OCPPPP_GENERATED_FILES}")
  add_dependencies(${TARGET_NAME} ocpppp_${TARGET_NAME}_headers)
endfunction(ocpppp_generate)
