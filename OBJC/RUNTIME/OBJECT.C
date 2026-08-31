#include "OBJC/OBJC.H"

id
object_alloc (Class cls)
{
    if (!cls)
        return nil;

    id obj = (id)objc_calloc (1, cls->size);
    if (obj)
    {
        object_setClass (obj, cls);
        obj->ref_count = 1;
        return obj;
    }
    return nil;
}

void
object_dealloc (id obj)
{
    if (!obj)
        return;
    objc_free (obj);
}

void
object_retain (id obj)
{
    if (!obj)
        return;
    obj->ref_count++;
}

uint32_t
object_refCount (id obj)
{
    return obj->ref_count;
}