#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "OBJC/OBJC.H"

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

- (Class)class
{
    return object_getClass (self);
}

+ (Class)class
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
