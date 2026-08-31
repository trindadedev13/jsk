#ifndef OBJC_H
#define OBJC_H

#include "OBJC/RUNTIME.H"

/** Include GNU ABI */
#include "OBJC/GNU.H"

#ifdef __OBJC__
/** Include Protocols first */
#include "OBJC/OBJECT+PROTOCOL.H"

/** Now the classes */
#include "OBJC/OBJECT.H"
#include "OBJC/PROTOCOL.H"
#endif

#endif
