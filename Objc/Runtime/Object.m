#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Objc/Objc.h"

id
object_alloc (Class cls)
{
    if (!cls)
        return nil;

    id obj = (id)objc_calloc (1, cls->size);
    if (obj)
    {
        object_setClass (obj, cls);
        obj->ref_count = 1;
        return obj;
    }
    return nil;
}

void
object_dealloc (id obj)
{
    if (!obj)
        return;
    objc_free (obj);
}

void
object_retain (id obj)
{
    if (!obj)
        return;
    obj->ref_count++;
}

uint32_t
object_refCount (id obj)
{
    return obj->ref_count;
}

void
object_release (id obj)
{
    if (!obj)
        return;

    if (obj->ref_count == 0)
        return;

    obj->ref_count--;

    if (obj->ref_count == 0)
        [obj dealloc];
}

@implementation Object

+ (void)initialize
{

}

+ (id)alloc
{
    return object_alloc(self);
}

- (id)init
{
    return self;
}

- (void)dealloc
{
    object_dealloc (self);
}

- (Class)__OBJC_OBJECT_CLASS_METHOD_NAME
{
    return object_getClass (self);
}

+ (Class)__OBJC_OBJECT_CLASS_METHOD_NAME
{
    return self;
}

- (Class)superclass
{
    return object_getSuperclass (self);
}

+ (Class)superclass
{
    return class_getSuperclass (self);
}

+ (const char *)name
{
    return class_getName (self);
}

- (BOOL)isEqual:(id)other
{
    return self == other;
}

- (BOOL)isKindOfClass:(Class)cls
{
    return object_isKindOfClass (self, cls);
}

+ (BOOL)conformsTo:(Protocol *)proto
{
    return class_conformsTo (self, proto);
} 

- (BOOL)conformsTo:(Protocol *)proto
{
    return class_conformsTo (object_getClass (self), proto);
}

- (BOOL)respondsToSelector:(SEL)sel
{
    return object_respondsToSelector (self, sel);
}

// Retain
- (id)retain
{
    object_retain (self);
    return self;
}

- (void)release
{
    object_release (self);
}

- (id)autorelease
{
    object_autorelease (self);
    return self;
}

- (uint32_t)refCount
{
    return object_refCount(self);
}

@end
