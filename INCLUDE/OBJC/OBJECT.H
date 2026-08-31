#ifndef OBJC_OBJECT_M
#define OBJC_OBJECT_M

#include <stdint.h>

OBJC_ROOT_CLASS
@interface Object <ObjectProtocol, RetainProtocol> {
    Class isa;
    uint32_t ref_count;
}

+ (void)initialize;
+ (id)alloc;
- (void)dealloc;
- (id)init;
- (Class)class;
+ (Class)class;
- (Class)superclass;
+ (Class)superclass;
+ (const char *)name;
- (BOOL)isEqual:(id)other;
- (BOOL)isKindOfClass:(Class)cls;
+ (BOOL)conformsTo:(Protocol *)proto;
- (BOOL)conformsTo:(Protocol *)proto;

- (id)retain;
- (void)release;
- (id)autorelease;
- (uint32_t)refCount;

@end

#endif
