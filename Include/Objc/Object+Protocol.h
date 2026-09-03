#pragma once

/**
 * Protocol which Object class should implement.
 */
@protocol ObjectProtocol
@required

/**
 * Returns the name of the Object.
 */
+ (const char *)name;

/**
 * Compares 'self' with given object.
 */
- (BOOL)isEqual:(id)other;

/**
 * Checks if 'self' derives from given class.
 */
- (BOOL)isKindOfClass:(Class)cls;

/**
 * Checks if 'self' implements given protocol.
 */
- (BOOL)conformsTo:(Protocol *)proto;

/**
 * Checks if 'self' responds for given selector.
 */
- (BOOL)respondsToSelector:(SEL)sel;

@end
