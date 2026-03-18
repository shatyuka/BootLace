macro(edk2_add_package name package)
    set(OUTPUT_FILE ${name}.efi)
    set(BUILD_PATH Build/${name}/${EDK2_TARGET}_${EDK2_TOOLCHAIN})
    set(CSCOPE_FILES ${BUILD_PATH}/CompileInfo/cscope.files)
    cmake_path(REMOVE_FILENAME CMAKE_C_COMPILER OUTPUT_VARIABLE COMPILER_PATH)
    if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${CSCOPE_FILES})
        file(STRINGS ${CMAKE_CURRENT_BINARY_DIR}/${CSCOPE_FILES} CSCOPE_FILES_LIST)
    endif ()
    add_custom_command(OUTPUT ${OUTPUT_FILE}
            DEPENDS ${CSCOPE_FILES_LIST}
            COMMAND sh ${CMAKE_SOURCE_DIR}/edk2/build.sh ${COMPILER_PATH} ${EDK2_PATH} ${EDK2_ARCH} ${EDK2_TOOLCHAIN} ${EDK2_TARGET} ${package}
            COMMAND ${CMAKE_COMMAND} -E copy ${BUILD_PATH}/${EDK2_ARCH}/${name}.efi ${OUTPUT_FILE}
            COMMAND ${CMAKE_COMMAND} -E copy ${BUILD_PATH}/CompileInfo/compile_commands.json compile_commands.json
            BYPRODUCTS report.txt compile_commands.json
    )
    add_custom_target(${name}
            DEPENDS ${OUTPUT_FILE}
            SOURCES ${CSCOPE_FILES_LIST}
    )
endmacro()
