#include "OBJC/OBJC.H"

#include <string.h>

#include "OBJC/RUNTIME_INTERNAL.H"

#define CLASS_TABLE_SIZE 32

Class class_table[CLASS_TABLE_SIZE + 1];

void
__objc_class_init (void)
{
    static BOOL init = NO;
    if (init)
        return;
    init = YES;

    for (int i = 0; i <= CLASS_TABLE_SIZE; i++)
        class_table[i] = Nil;
}

BOOL
__objc_class_register (Class cls)
{
    if (!cls || !cls->name)
        return NO;

    for (int i = 0; i < CLASS_TABLE_SIZE; i++)
    {
        if (class_table[i] == cls)
            return YES;

        if (class_table[i] == Nil)
        {
            class_table[i] = cls;

            if (cls->protocols)
                __objc_protocol_list_register (cls->protocols);

            return YES;
        }

        if (strcmp (cls->name, class_table[i]->name) == 0)
            objc_printf ("duplicated class named: %s\n", cls->name);
    }

    objc_panic ("class table is full. cannot register class: %s\n", cls->name);
}

BOOL
__objc_class_register_method_list (Class cls, MethodList *ml)
{
    if (!ml)
        return NO;

    for (int i = 0; i < ml->count; i++)
    {
        Method *m = &ml->methods[i];
        if (!m || !m->name || !m->imp)
            continue;

        HashItem *item = __objc_hash_register (cls, m->name, m->types, m->imp);
        if (!item)
            objc_panic ("failed to register method %s in class %s\n", m->name,
                        cls->name);

        item = __objc_hash_register (cls, m->name, NULL, m->imp);
        if (!item)
            objc_panic ("failed to register method %s in class %s\n", m->name,
                        cls->name);
    }

    return YES;
}

BOOL
__objc_class_register_methods (Class cls)
{
    if (cls->info & objc_class_flag_resolved)
        return YES;

    cls->info |= objc_class_flag_resolved;

    for (MethodList *ml = cls->methods; ml; ml = ml->next)
        __objc_class_register_method_list (cls, ml);

    if (cls->superclass != NULL)
    {
        if (cls->info & objc_class_flag_meta)
            return YES;

        Class superclass = objc_lookup_class ((const char *)cls->superclass);
        if (!superclass)
            objc_panic ("superclass %s not found for %s\n",
                        (const char *)cls->superclass, cls->name);

        // update the superclass pointer to the actual superclass
        cls->superclass = superclass;
    }

    return YES;
}

static Class
__objc_class_table_lookup (const char *name)
{
    if (!name)
        return Nil;

    for (int i = 0; i < CLASS_TABLE_SIZE; i++)
    {
        if (!class_table[i] || !class_table[i]->name)
            continue;

        if (strcmp (class_table[i]->name, name) == 0)
            return class_table[i];
    }

    return Nil;
}

Class
objc_lookup_class (const char *name)
{
    Class cls = __objc_class_table_lookup (name);
    if (!cls)
        return Nil;

    if (cls->info & objc_class_flag_resolved)
    {
        if (cls->isa && !(cls->isa->info & objc_class_flag_resolved))
        {
            // need to resolve metaclass
        }
        else
        {
            return cls;
        }
    }

    __objc_class_register_methods (cls);

    if (cls->isa && cls->superclass)
        cls->isa->superclass = cls->superclass->isa;

    if (cls->isa)
        __objc_class_register_methods (cls->isa);

    return cls;
}

Class
objc_lookupClass (const char *name)
{
    return name ? objc_lookup_class (name) : Nil;
}

const char *
class_getName (Class cls)
{
    return cls ? cls->name : NULL;
}

Class
object_getClass (id obj)
{
    return obj ? obj->isa : Nil;
}

const char *
object_getClassName (id obj)
{
    return obj ? obj->isa->name : NULL;
}

void
object_setClass (id obj, Class cls)
{
    if (!obj || !cls)
        objc_panic ("object or class is nil");

    if (cls->info & objc_class_flag_meta)
        objc_panic ("cannot set class of metaclass");

    obj->isa = cls;
}

BOOL
object_isKindOfClass (id obj, Class cls)
{
    if (!obj)
        return NO;

    if (!cls)
        objc_panic ("Class is Nil");

    Class objcls = obj->isa;
    while (objcls)
    {
        if (objcls == cls)
            return YES;
        objcls = objcls->superclass;
    }

    return NO;
}

size_t
class_getInstanceSize (Class cls)
{
    return cls ? cls->size : 0;
}

Class
object_getSuperclass (id obj)
{
    return obj ? obj->isa->superclass : Nil;
}

Class
class_getSuperclass (Class cls)
{
    return cls ? cls->superclass : Nil;
}
