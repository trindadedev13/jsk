#ifndef OBJC_PROTOCOL_H
#define OBJC_PROTOCOL_H

@interface Protocol : Object {
@private
    const char *_name;
}

- (const char *)name;
- (BOOL)conformsTo: (Protocol *)proto;

@end

#endif
