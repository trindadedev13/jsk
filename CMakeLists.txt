CMAKE_MINIMUM_REQUIRED (VERSION 3.22)

PROJECT (JSK
        LANGUAGES
                C CXX OBJC ASM_NASM)

SET (CMAKE_C_STANDARD 23)

SET (INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
SET (BUILD_DIR   ${CMAKE_BINARY_DIR})
SET (KERNEL_BIN  ${BUILD_DIR}/Kernel.bin)
SET (IMAGE       ${BUILD_DIR}/JSK.IMG)

MESSAGE (STATUS "Building with MULTIBOOT support")

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    ADD_COMPILE_DEFINITIONS(-DOBJC_DEBUG)
ENDIF()

# GLOBAL CONFIG
INCLUDE_DIRECTORIES (Include)
INCLUDE_DIRECTORIES (Include/Libc)
INCLUDE_DIRECTORIES (Include/Objc)

SET (_SC_FLAGS "-Wall -Wextra -nostdinc -fno-builtin -fno-stack-protector")
SET (_SL_FLAGS "-nostdlib -nodefaultlibs")

SET (CMAKE_C_FLAGS    "${CMAKE_C_FLAGS} ${_SC_FLAGS}")
SET (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${_SC_FLAGS} -nostdinc++")
SET (CMAKE_OBJC_FLAGS "${CMAKE_OBJC_FLAGS} ${_SC_FLAGS} -nostdinc++ -fobjc-runtime=gcc")

SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${_SL_FLAGS}")

ADD_SUBDIRECTORY (Libc)

## Objective C
ADD_SUBDIRECTORY (Objc/Runtime)
ADD_SUBDIRECTORY (Objc/Foundation)

ADD_SUBDIRECTORY (Multiboot)
ADD_SUBDIRECTORY (Kernel)
ADD_SUBDIRECTORY (Graphics)
ADD_SUBDIRECTORY (Cpu)

FIND_PROGRAM (GRUB_MKRESCUE grub-mkrescue)
IF (NOT GRUB_MKRESCUE)
        MESSAGE (FATAL_ERROR "grub-mkrescue not found - install grub2 + xorriso")
ENDIF ()

SET (ISO_ROOT     ${BUILD_DIR}/IsoRoot)
SET (GRUB_CFG_IN  ${CMAKE_SOURCE_DIR}/Multiboot/Grub.cfg)
SET (GRUB_CFG_OUT ${ISO_ROOT}/boot/grub/grub.cfg)

ADD_CUSTOM_COMMAND (
        OUTPUT ${GRUB_CFG_OUT} ${ISO_ROOT}/boot/Kernel.bin

        COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_ROOT}/boot/grub
        COMMAND ${CMAKE_COMMAND} -E copy ${KERNEL_BIN} ${ISO_ROOT}/boot/Kernel.bin
        COMMAND ${CMAKE_COMMAND} -E copy ${GRUB_CFG_IN} ${GRUB_CFG_OUT}

        DEPENDS
                ${KERNEL_BIN}
                ${GRUB_CFG_IN}

        VERBATIM)

ADD_CUSTOM_COMMAND (
        OUTPUT ${IMAGE}

        COMMAND ${GRUB_MKRESCUE} -o ${IMAGE} ${ISO_ROOT}

        DEPENDS
                ${GRUB_CFG_OUT}
                ${ISO_ROOT}/boot/Kernel.bin

        VERBATIM)

ADD_CUSTOM_TARGET (JSK ALL
        DEPENDS ${IMAGE})

ADD_DEPENDENCIES (JSK KERNEL)
