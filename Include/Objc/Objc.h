#ifndef OBJC_H
#define OBJC_H

#include "Objc/Runtime.h"

/** Include ABI Structures */
#include "Objc/Abi.h"

#ifdef __OBJC__

/** Include Protocols first */
#include "Objc/Object+Protocol.h"
#include "Objc/Alloc+Protocol.h"
#include "Objc/Retain+Protocol.h"

/** Now the classes */
#include "Objc/Object.h"
#include "Objc/Protocol.h"
#endif

#endif
