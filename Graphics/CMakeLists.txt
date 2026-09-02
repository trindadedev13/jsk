SET (SOURCES
        DefFont.c
        Context.m
        Font.m
        Surface.m)

INCLUDE (${CMAKE_SOURCE_DIR}/CMake/FixExts.cmake)

ADD_LIBRARY (GRAPHICS_OBJS
        OBJECT
        ${SOURCES})