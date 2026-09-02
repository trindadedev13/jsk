ADD_CUSTOM_COMMAND (
        OUTPUT ${BOOT_BIN}

        COMMAND nasm
                -f bin
                -I${CMAKE_SOURCE_DIR}/
                -I${CMAKE_SOURCE_DIR}/INCLUDE/
                ${CMAKE_CURRENT_SOURCE_DIR}/BOOT.ASM
                -o ${BOOT_BIN}

        DEPENDS
                ${CMAKE_CURRENT_SOURCE_DIR}/BOOT.ASM

        VERBATIM)

ADD_CUSTOM_TARGET (BOOT
        DEPENDS ${BOOT_BIN})
