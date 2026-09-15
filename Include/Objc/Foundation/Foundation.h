#pragma once

#include "Objc/Objc.h"

#ifdef __OBJC__

// Forward Declarations
@class NSObject;
@class NSAutoreleasePool;
@class NSConstantString;
@class NSString;

/// Protocols
#include "Foundation/NSConstantString+Protocol.h"

// Classes
#include "Foundation/NSObject.h"
#include "Foundation/NSAutoreleasePool.h"
#include "Foundation/NSConstantString.h"
#include "Foundation/NSString.h"

#endif