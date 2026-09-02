#pragma once

@interface NSAutoreleasePool : NSObject <RetainProtocol> {
@public
    id *objects;
    unsigned int count;
    unsigned int capacity;

    NSAutoreleasePool *previous;
}

- (id)init;
- (void)drain;

@end
