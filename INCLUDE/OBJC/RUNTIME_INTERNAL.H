#ifndef OBJC_RUNTIME_INTERNAL_H
#define OBJC_RUNTIME_INTERNAL_H

#include "OBJC/OBJC.H"

/*
 * Objective-C runtime hash table for selectors.
 * This structure is used to store and manage selectors in the Objective-C
 * runtime.
 */
typedef struct objc_hashitem_t
{
    Class cls;          // Pointer to the class that owns this selector
    const char *method; // Key for the selector, typically the selector name
    const char *types;  // Types encoding for the selector
    IMP imp;            // Implementation pointer for the selector
} HashItem;

void __objc_class_init (void);
BOOL __objc_class_register (Class cls);
BOOL __objc_class_register_method_list (Class, MethodList *);

void __objc_protocol_init (void);
BOOL __objc_protocol_register (Protocol *);
BOOL __objc_protocol_list_register (ProtocolList *);

void __objc_hash_init (void);
HashItem *__objc_hash_register (Class, const char *, const char *, IMP);
HashItem *__objc_hash_lookup (Class, const char *, const char *);

void __objc_category_init (void);
BOOL __objc_category_register (Category *);
BOOL __objc_category_load (void);

void __objc_statics_init (void);
BOOL __objc_statics_register (StaticInstancesList *);
BOOL __objc_statics_load (void);

#endif
