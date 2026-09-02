SET (SOURCES
        CM_ENTRY
        GDT.ASM
        MAIN.C)

SET (DEPS 
        KERNEL_OBJS
        GRAPHICS_OBJS
        BIOS_OBJS)

SET (DEPS_OBJS
        $<TARGET_OBJECTS:KERNEL_OBJS>
        $<TARGET_OBJECTS:GRAPHICS_OBJS>
        $<TARGET_OBJECTS:BIOS_OBJS>)

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
                -T ${${CMAKE_SOURCE_DIR}/BOOT/LINKER.LD}
                ${DEPS_OBJS}
                -o ${KERNEL_BIN}

        DEPENDS
                ${DEPS}

        COMMAND_EXPAND_LISTS
        VERBATIM)

ADD_CUSTOM_TARGET (KERNEL ALL
        DEPENDS ${KERNEL_BIN})

ADD_DEPENDENCIES (KERNEL ${DEPS})