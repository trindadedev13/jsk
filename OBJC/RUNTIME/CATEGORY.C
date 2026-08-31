#include "OBJC/OBJC.H"

#include "OBJC/RUNTIME_INTERNAL.H"

#define CATEGORY_TABLE_SIZE 32
static Category *category_table[CATEGORY_TABLE_SIZE + 1];

void
__objc_category_init ()
{
    static BOOL init = NO;
    if (init)
        return;
    init = YES;

    for (int i = 0; i <= CATEGORY_TABLE_SIZE; i++)
        category_table[i] = NULL;
}

BOOL
__objc_category_register (Category *cat)
{
    if (!cat || !cat->name || !cat->classname)
        return NO;

    for (int i = 0; i < CATEGORY_TABLE_SIZE; i++)
    {
        if (category_table[i] == cat)
            return YES;
        if (!category_table[i])
        {
            category_table[i] = cat;
            return YES;
        }
    }

    objc_panic ("category table is full. cannot register category %s\n",
                cat->name);
}

static BOOL
__objc_load_category (Category *cat)
{
    Class cls = objc_lookup_class (cat->classname);
    if (!cls)
        return NO;

    if (cat->instance_methods)
    {
        for (MethodList *ml = cat->instance_methods; ml; ml = ml->next)
            __objc_class_register_method_list (cls, ml);
    }

    return YES;
}

BOOL
__objc_category_load (void)
{
    static BOOL init = NO;
    if (init)
        return YES;
    init = YES;

    for (int i = 0; i < CATEGORY_TABLE_SIZE; i++)
    {
        Category *cat = category_table[i];
        if (!cat)
            continue;
        __objc_load_category (cat);
    }

    return YES;
}
