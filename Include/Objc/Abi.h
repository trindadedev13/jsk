#ifndef OBJC_ABI_H
#define OBJC_ABI_H

/**
 * This file defines all structures bodies used in the Runtime.
 * including GCC Abi and others.
 */

#include <stddef.h>
#include <stdint.h>

#include "Objc/Runtime.h"

#define OBJC_GNU_ABI_VERSION 8

#define OBJC_OBJECT_BODY                                                      \
    Class isa;                                                                \
    size_t ref_count

typedef struct objc_super_t
{
    id receiver;
    Class superclass;
} SUPER;

typedef struct objc_symtab_t
{
    unsigned long
        selector_count; /** number of selectors referenced in this module */
    struct objc_selector_t
        *selectors; /** selectors referenced in this module */

    unsigned short class_count; /** number of classes defined in this module */
    unsigned short
        category_count; /** number of categories defined in this module */

    void *defs[1]; /** definitions of classes, categories and static objects */
} SymTable;

typedef struct objc_ivar_t
{
    const char *name;
    const char *type;
    int offset;
} Ivar;

typedef struct objc_ivar_list_t
{
    int count;
    Ivar ivars[1];
} IvarList;

typedef struct objc_method_t
{
    union
    {
        const char *name;
        SEL sel;
    };

    const char *types;
    IMP imp;
} Method;

typedef struct objc_method_list_t
{
    struct objc_method_list_t *next; /** next list in this chain */

    int count; /** number of methods in this list */
    Method methods[1];
} MethodList;

typedef enum objc_class_flag_t
{
    objc_class_flag_meta = 0x02,
    objc_class_flag_initialized = 0x04,
    objc_class_flag_resolved = 0x08,
} ClassFlag;

typedef struct objc_protocol_list_t
{
    struct objc_protocol_list_t *next; // next list of protocols
    size_t count;
    Protocol *protocols[1];
} ProtocolList;

typedef struct objc_category_t
{
    const char *name;
    const char *classname;

    MethodList *instance_methods;
    MethodList *class_methods;
    ProtocolList *protocols;
} Category;

typedef struct objc_static_instances_list
{
    const char *classname;
    id instances[1];
} StaticInstancesList;

typedef struct objc_module_t
{
    unsigned long version;
    unsigned long size;
    const char *name;
    SymTable *symtab;
} Module;

struct objc_selector_t
{
    union
    {
        const char *name;
        size_t id;
    };
    char *type;
};

/**
 * Represents any object that inherits from Object root class.
 * Any valid object should be possible to cast to this.
 * see @macro OBJC_OBJECT_BODY.
 */
struct objc_object_t
{
    OBJC_OBJECT_BODY;
};

struct objc_protocol_t
{
    OBJC_OBJECT_BODY; /** Protocol is a Object */

    const char *name;

    ProtocolList *protocols;
    MethodList *instance_methods;
    MethodList *class_methods;
};

struct objc_class_t
{
    Class isa;
    Class superclass;

    const char *name;
    long version;
    unsigned long info;
    unsigned long size;

    struct objc_ivar_list_t *ivars;
    struct objc_method_list_t *methods;

    void **dtable;

    struct objc_class_t *subclass_list;
    struct objc_class_t *siblings_classes;

    struct objc_protocol_list_t *protocols;

    void *extra;
};

struct objc_autorelease_pool_t
{
    OBJC_OBJECT_BODY; /** NSAutoreleasePool is a Object */

    id *objects;
    unsigned int count;
    unsigned int capacity;

    struct objc_autorelease_pool_t *previous;
};

#endif
