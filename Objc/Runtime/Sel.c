#include "Objc/Objc.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct objc_selector_entry_t
{
    SEL sel;
    size_t id;
} SelectorEntry;

typedef struct objc_selector_entry_list_t
{
    SelectorEntry *entries;
    size_t count;
    size_t capacity;
} SelectorList;

static SelectorList list = { 0 };
static size_t next_id = 1;

static void
__objc_push_sel (SEL sel)
{
    if (list.capacity == 0)
    {
        list.capacity = 16;
        list.entries = objc_calloc (list.capacity, sizeof *list.entries);
    }

    if (list.count == list.capacity)
    {
        list.capacity *= 2;

        list.entries = objc_realloc (list.entries,
                                     list.capacity * sizeof *list.entries);
    }

    list.entries[list.count].sel = sel;
    list.entries[list.count].id = next_id++;

    list.count++;
}

static SelectorEntry *
__objc_find_sel (const char *name)
{
    for (size_t i = 0; i < list.count; i++)
    {
        if (strcmp (list.entries[i].sel->name, name) == 0)
            return &list.entries[i];
    }

    return NULL;
}

static SelectorEntry *
__objc_find_sel_by_pointer (SEL sel)
{
    for (size_t i = 0; i < list.count; i++)
    {
        if (list.entries[i].sel == sel)
            return &list.entries[i];
    }

    return NULL;
}

SEL
sel_registerTypedName (const char *name, const char *type)
{
    if (!name)
        return NULL;

    SelectorEntry *entry = __objc_find_sel (name);

    if (entry)
    {
        if (type)
        {
            if (entry->sel->type)
                free (entry->sel->type);

            entry->sel->type = strdup (type);
        }

        return entry->sel;
    }

    SEL sel = objc_calloc (1, sizeof *sel);

    sel->name = strdup (name);
    sel->type = type ? strdup (type) : NULL;

    __objc_push_sel (sel);

    return sel;
}

SEL
sel_registerName (const char *name)
{
    return sel_registerTypedName (name, NULL);
}

const char *
sel_getName (SEL sel)
{
    if (!sel)
        return NULL;

    return sel->name;
}

size_t
sel_getId (SEL sel)
{
    SelectorEntry *entry;

    if (!sel)
        return 0;

    entry = __objc_find_sel_by_pointer (sel);

    if (!entry)
        return 0;

    return entry->id;
}
