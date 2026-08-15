SET (SOURCES
        GRAPHICS.C)

INCLUDE (${CMAKE_SOURCE_DIR}/CMAKE/FIXEXTS.CMAKE)

ADD_LIBRARY (GRAPHICS_OBJS
        OBJECT
        ${SOURCES})

TARGET_INCLUDE_DIRECTORIES (GRAPHICS_OBJS PRIVATE
        ${INCLUDE_DIR})

TARGET_COMPILE_OPTIONS (GRAPHICS_OBJS PRIVATE
        $<$<COMPILE_LANGUAGE:C,CXX>:
        -Wall -Wextra -pedantic -pedantic-errors
        -nostdlib -nostdinc++ -nodefaultlibs
        -fno-builtin -fno-stack-protector>)