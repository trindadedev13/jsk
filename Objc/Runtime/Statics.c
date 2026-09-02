#include "Objc/RuntimeInternal.h"

#define STATICS_TABLE_SIZE 32
static StaticInstancesList *statics_table[STATICS_TABLE_SIZE + 1];

void
__objc_statics_init ()
{
    static BOOL init = NO;
    if (init)
        return;
    init = YES;

    for (int i = 0; i <= STATICS_TABLE_SIZE; i++)
        statics_table[i] = NULL;
}

BOOL
__objc_statics_register (StaticInstancesList *list)
{
    if (!list || !list->classname)
        return NO;

    for (int i = 0; i < STATICS_TABLE_SIZE; i++)
    {
        if (statics_table[i] == list)
            return YES;
        if (statics_table[i] == NULL)
        {
            statics_table[i] = list;
            return YES;
        }
    }

    objc_panic ("Static instances table is full. cannot register class: %s\n",
                list->classname);
}

static void
__objc_statics_load_list (StaticInstancesList *list)
{
    Class cls = objc_lookup_class (list->classname);
    if (!cls)
        objc_panic ("static instances class %s not found\n", list->classname);

    for (id *instance = list->instances; *instance; instance++)
        (*instance)->isa = cls;
}

BOOL
__objc_statics_load ()
{
    static BOOL init = NO;
    if (init)
        return YES;
    init = YES;

    for (int i = 0; i < STATICS_TABLE_SIZE; i++)
    {
        StaticInstancesList *sil = statics_table[i];
        if (!sil)
            continue;
        __objc_statics_load_list (sil);
    }

    return YES;
}
