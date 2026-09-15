#include "Foundation/Foundation.h"

#include <stddef.h>
#include <string.h>

@implementation NSString

- (id)init
{
    self = [super init];
    if (self)
    {
        _value = _data = NULL;
        _len = _cap = 0;
    }

    return self;
}


- (id)initWithCapacity:(size_t)capacity
{
    self = [self init];
    if (!self) return nil;
    if (capacity == 0) return nil;

    _data = objc_malloc(capacity);
    if (!_data)
    {
        [self release];
        return nil;
    }

    memset(_data, 0, capacity);
    _value = _data;
    _len = 0;
    _cap = capacity;

    return self;
}

- (id)initWithString:(id<NSConstantStringProtocol, ObjectProtocol>)str
{
    self = [self init];
    if (!self) return nil;
    if (!str)
    {
        [self release];
        return nil;
    }

    if (object_getClass(str) == objc_lookupClass("NSConstantString"))
    {
        _value = [str cStr];
        _len = [str length];
    } 
    else if ([str isKindOfClass:[NSString class]])
    {
        _value = [str cStr];
        _len = [str length];
    }
    else
    {
        [self release];
        return nil;
    }
    return self;
}

- (id)initWithCString:(const char *)str
{
    self = [self init];
    if (!self) return nil;
    if (!str)
    {
        [self release];
        return nil;
    }

    _value = str;
    _len = strlen(str);

    return self;
}

+ (NSString *)new
{
    // todo: check autoreleasepool
    return [[[NSString alloc] init] autorelease];
}

+ (NSString *)stringWithCapacity:(size_t)capacity
{
    // todo: check autoreleasepool
    return [[[NSString alloc] initWithCapacity:capacity] autorelease];
}

+ (NSString *)stringWithString:(id<NSConstantStringProtocol, ObjectProtocol>)str
{
    // todo: check autoreleasepool
   return [[[NSString alloc] initWithString:str] autorelease];
}

+ (NSString *)stringWithCString:(const char *)str
{
    // todo: check autoreleasepool
   return [[[NSString alloc] initWithCString:str] autorelease];
}

- (void)dealloc
{
    if (_data)
        objc_free (_data);
    [super dealloc];
}

- (size_t)length
{
    return _len;
}

- (const char *)cStr
{
    return _value ? _value : "";
}

- (size_t)capacity
{
    return _cap;
}

- (BOOL)isEqual:(id)other
{
    if (self == other)return YES;
    if (other == nil || [other conformsTo:@protocol(NSConstantStringProtocol)] == NO)
        return NO;

    if ([other length] != _len)
        return NO;

    const char *otherRaw = [other cStr];
    if (otherRaw == _value) return YES;
    return strcmp(_value ? _value : "", otherRaw ? otherRaw : "") == 0;
}

- (BOOL)makeMutableWithCapacity:(size_t)cap
{
    size_t minReq = _len + 1;
    if (cap < minReq) cap = minReq;
    if (cap < _cap) cap = _cap;
    if (_data && _cap >= cap) return YES;
    if (!_data)
    {
        _data = objc_malloc(cap);
        if (!_data) return NO;
        if (_value && _len > 0)
        {
            memcpy(_data, _value, _len + 1);
        }
        else
        {
            memset(_data, 0, cap);
        }

        _value = _data;
        _cap = cap;
        return YES;
    }

    char *data = objc_malloc(cap);
    if (!data) return NO;

    if (_len > 0)
    {
        memcpy(_data, _value, _len + 1);
    }
    else
    {
        memset(_data, 0, cap);
    }

    objc_free(_data);
    _data = data;
    _value = _data;
    _cap = cap;
    return YES;
}

- (BOOL)append:(id<NSConstantStringProtocol, ObjectProtocol>)str
{
    if (!str) return NO;
    size_t strLen = [str length];
    if (strLen == 0) return NO;

    if ([self makeMutableWithCapacity:_len + strLen + 1] == NO)
        return NO;

    memcpy(_data + _len, [str cStr], strLen + 1);
    _len += strLen;

    return YES;
}

- (BOOL)appendCString:(const char *)str
{
    if (!str) return NO;
    size_t strLen = strlen(str);
    if (strLen == 0) return 0;
    
    if ([self makeMutableWithCapacity:_len + strLen + 1] == NO)
            return NO;

    memcpy(_data + _len, str, strLen + 1);
    _len += strLen;
    return YES;
}



@end
