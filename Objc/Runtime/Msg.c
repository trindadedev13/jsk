#include "Objc/Objc.h"

#include "Objc/RuntimeInternal.h"

static id
__objc_nil_method (id recv, SEL sel OBJC_UNUSED)
{
    return recv;
}

static IMP
__objc_msg_lookup (Class cls, SEL sel)
{
    if (!cls || !sel)
        return NULL;

    while (cls)
    {
        HashItem *item
            = __objc_hash_lookup (cls, sel_getName (sel), sel->type);
        if (item)
            return item->imp;
        cls = cls->superclass;
    }

    return NULL;
}

static BOOL
__objc_send_initialize (Class cls)
{
    if (!cls)
        return NO;

    // Don't call initialize on the same class twice
    if (cls->info & objc_class_flag_initialized)
        return YES;

    // Mark the class as initialized early to prevent recursion
    cls->info |= objc_class_flag_initialized;

    // If the superclass has an initialize method, call it first
    if (cls->superclass)
        __objc_send_initialize (cls->superclass);

    // Find and call the initialize method
    static SEL initialize = NULL;
    if (!initialize)
        initialize = sel_registerTypedName ("initialize", "v16@0:8");

    IMP imp
        = __objc_msg_lookup (cls, initialize); // Lookup the initialize method
    if (imp)
    {
        // Call the initialize method - suppress function cast warning as this
        // is a legitimate cast from variadic IMP to non-variadic function for
        // +initialize which takes no parameters
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"
        ((void (*) (id, SEL))imp) (
            (id)cls, initialize); // Call the initialize method on the class
#pragma GCC diagnostic pop
    }

    return YES;
}

/**
 * Message dispatch function. Returns the implementation pointer for
 * the specified selector. Returns the nil_method if the receiver is nil,
 * and panics if the selector is not found.
 */
IMP
objc_msg_lookup (id receiver, SEL selector)
{
    if (!receiver)
        return (IMP)__objc_nil_method;

    // First load the static instances and categories
    static BOOL init = NO;
    if (!init)
    {
        init = YES; // Set init to YES to prevent multiple initializations
        __objc_statics_load ();
        __objc_category_load ();
    }

    // Get the class of the receiver
    Class cls = receiver->isa;
    if (!cls)
        objc_panic ("receiver @%p class is Nil (selector=%s)", receiver,
                    sel_getName (selector));

    IMP imp = __objc_msg_lookup (cls, selector);
    if (!imp)
        objc_panic ("class=%c[%s %s] selector->types=%s cannot send "
                    "message\n",
                    receiver->isa->info & objc_class_flag_meta ? '+' : '-',
                    receiver->isa->name, sel_getName (selector),
                    selector->type);

    // If the class has of the receiver not been initialized, then this is the
    // time to do it
    Class meta_cls = cls->info & objc_class_flag_meta ? cls : cls->isa;
    if (!(meta_cls->info & objc_class_flag_initialized))
        // Call the class's initialize method
        __objc_send_initialize (meta_cls);

    return imp;
}

/**
 * Message superclass dispatch function. Returns the implementation pointer for
 * the specified selector, for the receiver superclass. Returns nil if the
 * receiver is nil.
 */
IMP
objc_msg_lookup_super (SUPER *super, SEL selector)
{
    if (!super || !super->receiver)
        return NULL;

    IMP imp = __objc_msg_lookup (super->superclass, selector);
    if (!imp)
    {
        objc_panic (
            "objc_msg_lookup: class=%c[%s %s] selector->types=%s not found\n",
            super->receiver->isa->info & objc_class_flag_meta ? '+' : '-',
            super->receiver->isa->name, sel_getName (selector),
            selector->type);
    }
    return imp;
}

///////////////////////////////////////////////////////////////////////////////

BOOL
class_respondsToSelector (Class cls, SEL selector)
{
    if (!cls)
        return NO;

    if (!selector)
        objc_panic ("SEL is NULL");

    return __objc_msg_lookup (cls, selector) == NULL
               ? NO
               : YES; // Check if the class responds to the selector
}

BOOL
object_respondsToSelector (id object, SEL selector)
{
    if (!object)
        return NO; // If the object is nil, it cannot respond to any selector

    if (!selector)
        objc_panic ("SEL is NULL");

    return __objc_msg_lookup (object_getClass (object), selector) == NULL
               ? NO
               : YES;
}

BOOL
class_metaclassRespondsToSelector (Class cls, SEL selector)
{
    if (!cls)
        return NO;
    if (!(cls->info & objc_class_flag_meta))
        cls = cls->isa; // Use the metaclass for class methods

    return class_respondsToSelector (
        cls, selector); // Check if the class responds to the selector
}