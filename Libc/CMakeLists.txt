CMAKE_MINIMUM_REQUIRED (VERSION 3.22)

SET (SOURCES
        String.c
        Malloc.c
        Print.c
        Printf.c
        Abort.c)

INCLUDE (${CMAKE_SOURCE_DIR}/CMake/FixExts.cmake)

ADD_LIBRARY (LIBC_OBJS
        OBJECT
        ${SOURCES})
