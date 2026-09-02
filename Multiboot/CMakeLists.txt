SET (SOURCES
        Boot.asm)

INCLUDE (${CMAKE_SOURCE_DIR}/CMake/FixExts.cmake)

ADD_LIBRARY (MULTIBOOT
        OBJECT
        ${SOURCES})