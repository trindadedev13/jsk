#include "OBJC/OBJC.H"

#include <stddef.h>
#include <string.h>

#include "OBJC/RUNTIME_INTERNAL.H"

#define PROTOCOL_TABLE_SIZE 32
static Protocol *protocol_table[PROTOCOL_TABLE_SIZE + 1];

void
__objc_protocol_init (void)
{
    static BOOL init = NO;
    if (init)
        return;
    init = YES;

    for (int i = 0; i <= PROTOCOL_TABLE_SIZE; i++)
        protocol_table[i] = NULL;
}

BOOL
__objc_protocol_register (Protocol *proto)
{
    if (!proto || !proto->name)
        return NO;

    for (int i = 0; i < PROTOCOL_TABLE_SIZE; i++)
    {
        if (protocol_table[i] == proto)
            return YES;

        if (!protocol_table[i])
        {
            protocol_table[i] = proto;
            return YES;
        }

        if (strcmp (protocol_table[i]->name, proto->name) == 0)
        {
            objc_printf ("warning: duplicate Protocol named %s\n",
                         proto->name);
            return YES;
        }
    }

    return NO;
}

BOOL
__objc_protocol_list_register (ProtocolList *list)
{
    if (!list)
        return NO;

    for (size_t i = 0; i < list->count; i++)
    {
        Protocol *p = list->protocols[i];
        if (p && p->name)
            __objc_protocol_register (p);
    }

    if (list->next)
        return __objc_protocol_list_register (list->next);

    return YES;
}

const char *
proto_getName (Protocol *proto)
{
    if (!proto || !proto->name)
        return NULL;
    return proto->name;
}

BOOL
proto_conformsTo (Protocol *proto, Protocol *other)
{
    if (!proto || !other)
        return NO;

    if (proto == other)
        return YES;

    if (strcmp (proto->name, other->name) == 0)
        return YES;

    ProtocolList *list = proto->protocols;
    while (list)
    {
        for (size_t i = 0; i < list->count; i++)
        {
            if (proto_conformsTo (list->protocols[i], other))
                return YES;
        }
        list = list->next;
    }

    return NO;
}

BOOL
class_conformsTo (Class cls, Protocol *other)
{
    if (!cls || !other)
        return NO;

    ProtocolList *list = cls->protocols;
    while (list)
    {
        for (size_t i = 0; i < list->count; i++)
        {
            if (proto_conformsTo (list->protocols[i], other))
                return YES;
        }
        list = list->next;
    }

    Class super = class_getSuperclass (cls);
    if (super)
        return class_conformsTo (super, other);

    return NO;
}
