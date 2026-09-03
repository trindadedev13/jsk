CMAKE_MINIMUM_REQUIRED (VERSION 3.22)

SET (SOURCES
        NSObject.m
        NSAutoreleasePool.m
        NSConstantString.m)

INCLUDE (${CMAKE_SOURCE_DIR}/CMake/FixExts.cmake)

ADD_LIBRARY (OBJC_FOUNDATION_OBJS
        OBJECT
        ${SOURCES})
