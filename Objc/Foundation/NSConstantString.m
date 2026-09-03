#include "Foundation/Foundation.h"

#include <stddef.h>
#include <string.h>

@implementation NSConstantString

+ (id)alloc
{
    return nil; /** NSConstantStrings should not be allocated. */
}

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-missing-super-calls"
#endif
- (void)dealloc
{
    
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif

- (id)retain
{
    /** NSConstantString is immutable, so we return itself */
    return self;
}

- (void)release
{
    /** NSConstantString is immutable, so we do nothing */
}

- (const char *)cStr
{
    return _data;
}

- (size_t)length
{
    return _length;
}

- (BOOL)isEqual:(id)other
{
    if (self == other) return YES;

    if ([other class] == [self class])
    {
        if (self->_length != ((NSConstantString *)other)->_length)
        return YES;

        return memcmp (self->_data, ((NSConstantString *)other)->_data, self->_length) == 0;
    }

    return NO;
}

@end
