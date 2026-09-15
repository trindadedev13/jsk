#pragma once

#include <stdarg.h>
#include <stddef.h>

#include <Foundation/Foundation.h>

@interface NSString : NSObject <NSConstantStringProtocol> {
@private
  const char *_value;
  char *_data;
  size_t _len;
  size_t _cap;
}

+ (NSString *)new;
+ (NSString *)stringWithCapacity:(size_t)cap;
+ (NSString *)stringWithString:
    (id<NSConstantStringProtocol, ObjectProtocol>)str;
+ (NSString *)stringWithCString:(const char *)str;

- (id)initWithCapacity:(size_t)cap;
- (id)initWithString:(id<NSConstantStringProtocol, ObjectProtocol>)str;
- (id)initWithCString:(const char *)str;

- (const char *)cStr;
- (size_t)length;
- (size_t)capacity;

- (BOOL)append:(id<NSConstantStringProtocol, ObjectProtocol>)str;
- (BOOL)appendCString:(const char *)str;

@end
