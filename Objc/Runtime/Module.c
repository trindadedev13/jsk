#include "Objc/Objc.h"

#include <stdlib.h>

#include "Objc/RuntimeInternal.h"

objc_malloc_t objc_malloc = malloc;
objc_calloc_t objc_calloc = calloc;
objc_realloc_t objc_realloc = realloc;
objc_free_t objc_free = free;

static BOOL
__objc_module_register (Module *mod)
{
    if (!mod || mod->version != OBJC_GNU_ABI_VERSION)
    {
        objc_panic ("Invalid ABI Version %d\n", mod->version);
        return NO;
    }

    struct objc_selector_t *refs = mod->symtab->selectors;
    if (refs && mod->symtab->selector_count > 0)
    {
    }

    objc_printf ("%s cls_def_cnt=%d cat_def_cnt=%d\n", mod->name,
                 mod->symtab->class_count, mod->symtab->category_count);

    unsigned short j = 0;
    for (unsigned short i = 0; i < mod->symtab->class_count; i++)
        __objc_class_register ((Class)mod->symtab->defs[j++]);

    for (unsigned short i = 0; i < mod->symtab->category_count; i++)
        __objc_category_register ((Category *)mod->symtab->defs[j++]);

    StaticInstancesList **statics = mod->symtab->defs[j];
    while (statics && *statics)
        __objc_statics_register (*(statics++));

    return YES;
}

void
__objc_exec_class (Module *mod)
{
    __objc_class_init ();
    __objc_hash_init ();
    __objc_statics_init ();
    __objc_category_init ();
    __objc_protocol_init ();
    __objc_module_register (mod);
}
