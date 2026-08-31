#ifndef OBJC_OBJECT_PROTOCOL_H
#define OBJC_OBJECT_PROTOCOL_H

@protocol ObjectProtocol
@required

+ (const char *)name;
- (BOOL)isEqual:(id)other;
- (BOOL)isKindOfClass:(Class)cls;
- (BOOL)conformsTo:(Protocol *)proto;
- (BOOL)respondsToSelector:(SEL)sel;

@end

#endif
