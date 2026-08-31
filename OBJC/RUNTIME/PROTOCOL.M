#import "OBJC/OBJC.H"

#include <string.h>

@implementation Protocol

- (const char *)name
{
    return _name;
}

+ (const char *)name
{
    return "Protocol";
}

- (BOOL)conformsTo:(Protocol *)proto
{
    return proto_conformsTo(self, proto);
}

- (BOOL)isEqual:(id)other
{
    if (self == other)
        return YES;

    if (object_getClass (self) != object_getClass (other))
        return NO;

    Protocol *proto = (Protocol *)other;
    return strcmp ([self name], [proto name]) == 0;
}

@end
