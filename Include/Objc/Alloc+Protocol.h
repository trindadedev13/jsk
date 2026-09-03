#pragma once

/**
 * Protocol for allocating and deallocating Objects.
 */
@protocol AllocProtocol
@required

/** 
 * Allocate a object and set it's required initial state.
 */
+ (id)alloc;

/**
 * Deallocate a object and free's it's memory.
 */
- (void)dealloc;

@end