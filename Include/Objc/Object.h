#pragma once

#include <stddef.h>

OBJC_ROOT_CLASS
@interface Object <ObjectProtocol, AllocProtocol, RetainProtocol> {
    OBJC_OBJECT_BODY;
}

#ifndef __cplusplus
#define __OBJC_OBJECT_CLASS_METHOD_NAME class
#else
#define __OBJC_OBJECT_CLASS_METHOD_NAME cls
#endif

+ (void)initialize;
+ (id)alloc;
- (void)dealloc;
- (id)init;

- (Class)__OBJC_OBJECT_CLASS_METHOD_NAME;
+ (Class)__OBJC_OBJECT_CLASS_METHOD_NAME;

- (Class)superclass;
+ (Class)superclass;

/** Object+Protocol */
+ (const char *)name;
- (BOOL)isEqual:(id)other;
- (BOOL)isKindOfClass:(Class)cls;
+ (BOOL)conformsTo:(Protocol *)proto;
- (BOOL)conformsTo:(Protocol *)proto;

/** Retain+Protocol */
- (id)retain;
- (void)release;

/** Add's this Object in current AutoreleasePool */
- (id)autorelease;

- (size_t)refCount;

@end