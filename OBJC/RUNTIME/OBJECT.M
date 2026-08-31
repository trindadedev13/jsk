#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "OBJC/OBJC.H"

extern void puts (const char *);

@implementation Object

+ (void)initialize
{

}

+ (id)alloc
{
    id obj = (id)objc_malloc(class_getInstanceSize (self));
    if (obj)
    {
        memset (obj, 0, class_getInstanceSize (self));
        object_setClass (obj, self);
    }

    return obj;
}

- (id)init
{
    return self;
}

- (void)dealloc
{
    objc_free (self);
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

@end
