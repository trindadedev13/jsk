SET (SOURCES
        ENTRY.ASM
        MAIN.M)

## I Don't Like this way of linking.
## Maybe at least an global list of deps
## where each Target includes it's deps
## and at end we link all here

SET (DEPS 
        MULTIBOOT
        KERNEL_OBJS
        GRAPHICS_OBJS
        CPU_OBJS
        LIBC_OBJS
        OBJC_RUNTIME_OBJS
        #OBJC_FOUNDATION_OBJS
        )

SET (DEPS_OBJS
        $<TARGET_OBJECTS:MULTIBOOT>
        $<TARGET_OBJECTS:KERNEL_OBJS>
        $<TARGET_OBJECTS:GRAPHICS_OBJS>
        $<TARGET_OBJECTS:CPU_OBJS>
        $<TARGET_OBJECTS:LIBC_OBJS>
        $<TARGET_OBJECTS:OBJC_RUNTIME_OBJS>
        #$<TARGET_OBJECTS:OBJC_FOUNDATION_OBJS>
        )

INCLUDE (${CMAKE_SOURCE_DIR}/CMAKE/FIXEXTS.CMAKE)

ADD_LIBRARY (KERNEL_OBJS
        OBJECT
        ${SOURCES})

ADD_CUSTOM_COMMAND (
        OUTPUT ${KERNEL_BIN}

        COMMAND ld.lld
                -m elf_i386
                -T ${CMAKE_SOURCE_DIR}/MULTIBOOT/LINKER.LD
                ${DEPS_OBJS}
                -o ${KERNEL_BIN}

        DEPENDS
                ${DEPS}

        COMMAND_EXPAND_LISTS
        VERBATIM)

ADD_CUSTOM_TARGET (KERNEL ALL
        DEPENDS ${KERNEL_BIN})

ADD_DEPENDENCIES (KERNEL ${DEPS})
