#ifndef OBJC_OBJECT_M
#define OBJC_OBJECT_M


OBJC_ROOT_CLASS
@interface Object <ObjectProtocol>
{
    Class isa;
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


@end

#endif
