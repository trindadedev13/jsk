#ifndef OBJC_H
#define OBJC_H

#include "OBJC/RUNTIME.H"

/** Include ABI Structures */
#include "OBJC/ABI.H"

#ifdef __OBJC__
/** Include Protocols first */
#include "OBJC/OBJECT+PROTOCOL.H"
#include "OBJC/RETAIN+PROTOCOL.H"

/** Now the classes */
#include "OBJC/OBJECT.H"
#include "OBJC/PROTOCOL.H"
#include "OBJC/NSAUTORELEASEPOOL.H"
#endif

#endif
