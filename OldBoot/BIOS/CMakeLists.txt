SET (SOURCES
        MODE.ASM
        VIDEO.ASM)

INCLUDE (${CMAKE_SOURCE_DIR}/CMAKE/FIXEXTS.CMAKE)

ADD_LIBRARY (BIOS_OBJS
        OBJECT
        ${SOURCES})

TARGET_INCLUDE_DIRECTORIES (BIOS_OBJS PRIVATE
        ${INCLUDE_DIR})

TARGET_COMPILE_OPTIONS (BIOS_OBJS PRIVATE
        $<$<COMPILE_LANGUAGE:C,CXX>:
        -Wall -Wextra -pedantic -pedantic-errors
        -nostdlib -nostdinc++ -nodefaultlibs
        -fno-builtin -fno-stack-protector>)