SET (SOURCES
        Cpu.asm)

INCLUDE (${CMAKE_SOURCE_DIR}/CMake/FixExts.cmake)

ADD_LIBRARY (CPU_OBJS
        OBJECT
        ${SOURCES})