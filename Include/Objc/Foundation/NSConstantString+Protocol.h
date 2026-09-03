#pragma once

#include <stddef.h>

/** 
 * This protocol defines the minimal interface that constant
 * string objects must implement to provide basic string functionality.
 * This enables different strings implementations to be used Polymorphically thoughout the framework.
 *
 * Classses conforming to this protocol can be used whenever basic string 
 * operations such as accessing C String representation 
 * or getting the length are required.
 */
@protocol NSConstantStringProtocol
@required

/**
 * Returns the C-String representation of the string.
 *
 * Returns a Null-terminated string that may not be modified or freed by the caller.
 */
- (const char *)cStr;

/**
 * Returns the length of the string in bytes not including the null-terminator.
 */
- (size_t)length;

@end
