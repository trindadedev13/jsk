#pragma once

#include <stddef.h>

@interface NSConstantString : NSObject <NSConstantStringProtocol> {
@private
    const char *_data;
    size_t _length;
}

/**
 * Returns the C-String representation of the string.
 *
 * Returns a Null-terminated C-String that may not be 
 * freed or modifier by the caller.
 */
- (const char *)cStr;

/** 
 * Returns the length of the string in bytes
 * not including the null-terminator
 */
- (size_t)length;

@end

#ifdef __clang__
/**
 * Provides a compability alias for `NSString`
 *
 * When compiling with clang. `NSConstantString` is aliased for 'NSString'
 * to allow for greatter compatibility with modern Objective-C code and 
 * frameworks.
 */
@compatibility_alias NSString NSConstantString;
#endif
