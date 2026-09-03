CMAKE_MINIMUM_REQUIRED (VERSION 3.22)

SET (SOURCES
        Class.c
        Module.c
        Hash.c
        Msg.c
        Statics.c
        Category.c
        Protocol.c
        Sel.c
        Object.m
        Protocol.m)

INCLUDE (${CMAKE_SOURCE_DIR}/CMake/FixExts.cmake)

ADD_LIBRARY (OBJC_RUNTIME_OBJS
        OBJECT
        ${SOURCES})
