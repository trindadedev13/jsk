#ifndef OBJC_RUNTIME_H
#define OBJC_RUNTIME_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** a pointer to an instance of a class */
typedef struct objc_object_t *id;

/** a pointer to a method selector */
typedef struct objc_selector_t *SEL;

/** a pointer to a class definition */
typedef struct objc_class_t *Class;

#ifdef __OBJC__
@class Protocol;
#else
typedef struct objc_protocol_t Protocol;
#endif

#ifdef __OBJC__
@class NSAutoreleasePool;
#else
typedef struct objc_autorelease_pool_t NSAutoreleasePool;
#endif

/** a pointer to a method implementation */
typedef id (*IMP) (id, SEL, ...);

/** this allows using custom allocators */
typedef void *(*objc_malloc_t) (size_t);
typedef void *(*objc_calloc_t) (size_t, size_t);
typedef void *(*objc_realloc_t) (void *, size_t);
typedef void (*objc_free_t) (void *);

extern objc_malloc_t objc_malloc;
extern objc_calloc_t objc_calloc;
extern objc_realloc_t objc_realloc;
extern objc_free_t objc_free;

/** a null object pointer */
#define nil ((id)0)

/** a null class pointer */
#define Nil ((Class)0)

/** Objective-C Boolean */
typedef bool BOOL;
#define YES true
#define NO false

/** 
 * This macros allows declaring classes without a SuperClass
 * if atttibute 'objc_root_class' is available.
 */
#if __has_attribute(objc_root_class)
#define OBJC_ROOT_CLASS __attribute__ ((objc_root_class))
#else
#define OBJC_ROOT_CLASS
#endif

#if __has_attribute(unused)
#define OBJC_UNUSED __attribute__ ((unused))
#else
#define OBJC_UNUSED
#endif

/** 
 * this macro is used in method declarations
 * to specify that the method accepts a variable argument
 * that must be terminated with 'nil'.
 */
#define OBJC_REQUIRES_NIL_TERMINATION

/** sets the allocator to be used in the runtime */
inline void
objc_setAllocator (objc_malloc_t om, objc_free_t of)
{
    objc_malloc = om;
    objc_free = of;
}

#ifndef objc_printf
#define objc_printf(fmt, ...) __objc_printf (fmt __VA_OPT__ (, ) __VA_ARGS__)

OBJC_UNUSED static void
__objc_printf (const char *fmt, ...)
{
    va_list va;
    va_start (va, fmt);
    printf ("objc: ");
    vprintf (fmt, va);
    va_end (va);
}
#endif

#ifdef OBJC_DEBUG
#ifndef objc_debug
#define objc_debug(fmt, ...) __objc_debug(__func__, fmt __VA_OPT__(, ) __VA_ARGS__)

OBJC_UNUSED static void
__objc_debug(const char *func_name, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    printf("objc-debug: [%s]: ", func_name);
    vprintf(fmt, va);
    va_end(va);
}
#endif
#else
#define objc_debug(...) ((void)0)
#endif

#ifndef objc_panic
#define objc_panic(fmt, ...)                                                  \
    __objc_panic (__func__, fmt __VA_OPT__ (, ) __VA_ARGS__)

[[noreturn]] OBJC_UNUSED static void
__objc_panic (const char *func_name, const char *fmt, ...)
{
    va_list va;
    va_start (va, fmt);
    printf ("objc-panic [%s]: ", func_name);
    vprintf (fmt, va);
    va_end (va);

    abort ();
}
#endif

/** looks by a class and returns it, if not found, returns 'Nil' */
Class objc_lookupClass (const char *name);

/** looks by a class and resolver it, if needed, if fail, returns 'Nil' */
Class objc_lookup_class (const char *name);

/** returns the name of given class, or 'NULL' if 'cls' is 'Nil' */
const char *class_getName (Class cls);

/** returns the superclass of given object, or 'Nil' if it is a root class */
Class class_getSuperclass (Class cls);

/** returns the instance size of given class, or '0' if it is 'Nil' */
size_t class_getInstanceSize (Class cls);

/** checks if given class object responds to given selector */
BOOL class_metaclassRespondsToSelector (Class cls, SEL sel);

/** checks if given class instance responds to given selector */
BOOL class_respondsToSelector (Class cls, SEL sel);

/** checks if given class conforms to given protocol */
BOOL class_conformsTo (Class cls, Protocol *proto);

/** return the class of given object, or 'Nil' if the 'obj' is 'nil' */
Class object_getClass (id obj);

/** returns the name of given object class, or 'NULL' if 'obj' is 'nil' */
const char *object_getClassName (id obj);

/** sets the class of given object if not 'nil' */
void object_setClass (id obj, Class cls);

/**
 * checks if given instance class responds to an selector
 * returns YES if so.
 */
BOOL object_respondsToSelector (id obj, SEL sel);

/** returns the superclass of given object, or 'Nil' if it is a root class */
Class object_getSuperclass (id obj);

/** checks if given instance class matches, or is a subclass of 'cls' */
BOOL object_isKindOfClass (id obj, Class cls);

SEL sel_registerTypedName (const char *name, const char *type);
SEL sel_registerName (const char *name);

/** returns the name of given selector */
const char *sel_getName (SEL sel);

/** returns the id of given selector */
uint32_t sel_getId (SEL sel);

/** returns the name of given protocol */
const char *proto_getName (Protocol *proto);

/** checks if given 'proto' conforms to 'otherProto' */
BOOL proto_conformsTo (Protocol *proto, Protocol *otherProto);

/**
 * allocate a object and sets required fields.
 *
 * you should use this instead @objc_malloc.
 */
id object_alloc (Class cls);

/** free's the object from memory */
void object_dealloc (id obj);

/** increses object reference count */
void object_retain (id obj);

/**
 * decreases object reference count.
 *
 * if reference count reaches 0, it gets deallocated.
 */
void object_release (id obj);

/** returns the object reference count */
size_t object_refCount (id obj);

/**
 * add's the object in the current AutoreleasePool.
 *
 * NOTE: this function may be implemented in Foundation#NSAutoreleasePool!!!
 */
void object_autorelease (id obj);

#endif
