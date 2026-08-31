#pragma once

/** 
 * Protocol for retaining and Releasing objects 
 */
@protocol RetainProtocol
@required

/**
 * Increases the retain count of the receiver
 *
 * Sending a retain message to a object increses it's reference count by one.
 */
- (id)retain;

/**
 * Decreases the retain count of the receiver
 *
 * Sending a release message to a object decreases its reference count by one.
 * If the reference count hits 0, the object is deallocated.
 */
- (void)release;
@end
