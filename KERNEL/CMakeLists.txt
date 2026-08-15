SET (SOURCES
        MAIN.ASM
        KMAIN.C)

INCLUDE (${CMAKE_SOURCE_DIR}/CMAKE/FIXEXTS.CMAKE)

ADD_LIBRARY (KERNEL_OBJS
        OBJECT
        ${SOURCES})

TARGET_INCLUDE_DIRECTORIES (KERNEL_OBJS PRIVATE
        ${INCLUDE_DIR})

TARGET_COMPILE_OPTIONS (KERNEL_OBJS PRIVATE
        $<$<COMPILE_LANGUAGE:C,CXX>:
        -Wall -Wextra -pedantic -pedantic-errors
        -nostdlib -nostdinc++ -nodefaultlibs
        -fno-builtin -fno-stack-protector>)

ADD_CUSTOM_COMMAND (
        OUTPUT ${KERNEL_BIN}

        COMMAND ld.lld
                -m elf_i386
                -T ${CMAKE_SOURCE_DIR}/LINKER.LD
                $<TARGET_OBJECTS:GRAPHICS_OBJS>
                $<TARGET_OBJECTS:KERNEL_OBJS>
                -o ${KERNEL_BIN}

        DEPENDS
                GRAPHICS_OBJS
                KERNEL_OBJS

        COMMAND_EXPAND_LISTS
        VERBATIM)

ADD_CUSTOM_TARGET (KERNEL ALL
        DEPENDS ${KERNEL_BIN})

ADD_DEPENDENCIES (KERNEL
        GRAPHICS_OBJS
        KERNEL_OBJS)