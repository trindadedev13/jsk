#include "OBJC/OBJC.H"

#include <stdlib.h>

static NSAutoreleasePool *current_pool = NULL;

void
object_autorelease(id obj)
{
    if (!obj)
        return;

    if (!current_pool)
    {
        [obj release];
        return;
    }

    objc_autorelease_pool_add(current_pool, obj);
}

void
objc_autorelease_pool_add(NSAutoreleasePool *pool, id obj)
{
    if (pool->count == pool->capacity)
    {
        unsigned int cap =
            pool->capacity ? pool->capacity * 2 : 16;

        pool->objects =
            (id *)objc_realloc(
                pool->objects,
                cap * sizeof(id)
            );

        pool->capacity = cap;
    }

    pool->objects[pool->count++] = obj;
}

void
objc_autorelease_pool_push(NSAutoreleasePool *pool)
{
    pool->objects = NULL;
    pool->count = 0;
    pool->capacity = 0;

    pool->previous = current_pool;
    current_pool = pool;
}

void
objc_autorelease_pool_pop(NSAutoreleasePool *pool)
{
    if (!pool)
        return;

    if (current_pool != pool)
        return;

    NSAutoreleasePool *previous = pool->previous;

    for (unsigned int i = 0; i < pool->count; i++)
        [pool->objects[i] release];

    objc_free(pool->objects);

    pool->objects = NULL;
    pool->count = 0;
    pool->capacity = 0;
    pool->previous = NULL;

    current_pool = previous;
}

@implementation NSAutoreleasePool
- (id)init
{
    self = [super init];
    if (self)
        objc_autorelease_pool_push (self);

    return self;
}

- (void)drain
{
    objc_autorelease_pool_pop (self);
}

- (void)dealloc
{
    [self drain];
    [super dealloc];
}

@end
