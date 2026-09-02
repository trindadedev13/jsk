#pragma once

@protocol ObjectProtocol
@required

+ (const char *)name;
- (BOOL)isEqual:(id)other;
- (BOOL)isKindOfClass:(Class)cls;
- (BOOL)conformsTo:(Protocol *)proto;
- (BOOL)respondsToSelector:(SEL)sel;

@end
