/** THIS IMPLEMENTATION USES A POOL ALLOCATOR */

#include "stdlib.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifndef POOL_SIZE
#define POOL_SIZE 0x1000
#endif

/*
 * Alignment required by malloc().
 *
 * 16 is enough for the usual i386/x86-64 ABI types and also keeps
 * block headers/payloads naturally aligned.
 */
#ifndef MALLOC_ALIGNMENT
#define MALLOC_ALIGNMENT 16
#endif

#define ALIGN_UP(value, alignment) \
    (((value) + (alignment) - 1) & ~((alignment) - 1))

typedef struct memory_block_t BLOCK;
typedef struct memory_man_t MANAGER;

struct memory_block_t
{
    BLOCK *next;
    size_t size;
};

struct memory_man_t
{
    /*
     * Force the beginning of the pool to be properly aligned.
     */
    uint8_t memory[POOL_SIZE] __attribute__ ((aligned (MALLOC_ALIGNMENT)));

    BLOCK *free_blocks;
};

static MANAGER man;
static int initialized = 0;


/*
 * Initialize the allocator.
 */
static void
init_manager (void)
{
    BLOCK *block;

    block = (BLOCK *)man.memory;

    block->next = NULL;
    block->size = POOL_SIZE - sizeof (BLOCK);

    man.free_blocks = block;

    initialized = 1;
}


/*
 * Align an allocation size.
 */
static size_t
align_size (size_t size)
{
    return ALIGN_UP (size, MALLOC_ALIGNMENT);
}


/*
 * Remove a block from the free list.
 *
 * 'previous' may be NULL when block is the first element.
 */
static void
remove_free_block (BLOCK *block, BLOCK *previous)
{
    if (previous)
        previous->next = block->next;
    else
        man.free_blocks = block->next;

    block->next = NULL;
}


/*
 * Insert a free block into the address-sorted free list.
 *
 * Returns the previous block.
 */
static BLOCK *
insert_free_block (BLOCK *block)
{
    BLOCK *previous = NULL;
    BLOCK *current = man.free_blocks;

    while (current && current < block)
    {
        previous = current;
        current = current->next;
    }

    block->next = current;

    if (previous)
        previous->next = block;
    else
        man.free_blocks = block;

    return previous;
}

/*
 * Allocate memory from the pool.
 */
void *
malloc (size_t size)
{
    BLOCK *block;
    BLOCK *previous;

    if (!initialized)
        init_manager ();

    if (size == 0)
        return NULL;

    /*
     * Check for overflow before alignment.
     */
    if (size > SIZE_MAX - (MALLOC_ALIGNMENT - 1))
        return NULL;

    size = align_size (size);

    previous = NULL;
    block = man.free_blocks;

    while (block)
    {
        if (block->size >= size)
        {
            size_t remaining;

            remaining = block->size - size;

            /*
             * Only split if the remainder can hold another complete
             * BLOCK plus at least one aligned byte of payload.
             */
            if (remaining >= sizeof (BLOCK) + MALLOC_ALIGNMENT)
            {
                BLOCK *new_block;

                new_block =
                    (BLOCK *)((uint8_t *)block
                              + sizeof (BLOCK)
                              + size);

                new_block->size = remaining - sizeof (BLOCK);
                new_block->next = block->next;

                if (previous)
                    previous->next = new_block;
                else
                    man.free_blocks = new_block;

                block->size = size;
                block->next = NULL;
            }
            else
            {
                /*
                 * Use the entire block.
                 */
                remove_free_block (block, previous);
            }

            return (uint8_t *)block + sizeof (BLOCK);
        }

        previous = block;
        block = block->next;
    }

    return NULL;
}


/*
 * Free memory.
 */
void
free (void *ptr)
{
    BLOCK *block;
    BLOCK *previous;
    BLOCK *next;

    if (!ptr)
        return;

    block = (BLOCK *)((uint8_t *)ptr - sizeof (BLOCK));

    /*
     * Insert it back into the address-sorted free list.
     */
    previous = insert_free_block (block);
    next = block->next;

    /*
     * Merge with the block after us first.
     */
    if (next &&
        (uint8_t *)block + sizeof (BLOCK) + block->size
        == (uint8_t *)next)
    {
        block->size += sizeof (BLOCK) + next->size;
        block->next = next->next;
    }

    /*
     * Then merge with the block before us.
     */
    if (previous &&
        (uint8_t *)previous + sizeof (BLOCK) + previous->size
        == (uint8_t *)block)
    {
        previous->size += sizeof (BLOCK) + block->size;
        previous->next = block->next;
    }
}


/*
 * Resize an allocation.
 */
void *
realloc (void *ptr, size_t newsize)
{
    BLOCK *block;
    BLOCK *next;
    BLOCK *previous;
    size_t oldsize;

    if (!ptr)
        return malloc (newsize);

    if (newsize == 0)
    {
        free (ptr);
        return NULL;
    }

    if (newsize > SIZE_MAX - (MALLOC_ALIGNMENT - 1))
        return NULL;

    newsize = align_size (newsize);

    block = (BLOCK *)((uint8_t *)ptr - sizeof (BLOCK));
    oldsize = block->size;

    /*
     * Nothing to do.
     */
    if (newsize == oldsize)
        return ptr;


    /*
     * SHRINK
     *
     * If the unused tail is large enough, turn it into a free block.
     */
    if (newsize < oldsize)
    {
        size_t remaining = oldsize - newsize;

        if (remaining >= sizeof (BLOCK) + MALLOC_ALIGNMENT)
        {
            BLOCK *tail;

            tail =
                (BLOCK *)((uint8_t *)block
                          + sizeof (BLOCK)
                          + newsize);

            tail->size = remaining - sizeof (BLOCK);
            tail->next = NULL;

            block->size = newsize;

            /*
             * Return the tail through free(), which will also
             * coalesce it with adjacent free blocks.
             */
            free ((uint8_t *)tail + sizeof (BLOCK));
        }

        return ptr;
    }


    /*
     * GROW IN PLACE
     *
     * Look for a free block immediately after this allocation.
     */
    next = man.free_blocks;
    previous = NULL;

    while (next && next < block)
    {
        previous = next;
        next = next->next;
    }

    /*
     * 'next' is the first free block after 'block'.
     */
    if (next &&
        (uint8_t *)block + sizeof (BLOCK) + oldsize
        == (uint8_t *)next)
    {
        size_t combined;
        size_t required;

        combined = oldsize + sizeof (BLOCK) + next->size;
        required = newsize;

        if (combined >= required)
        {
            size_t remaining = combined - required;

            /*
             * Consume the neighboring free block.
             */
            if (remaining >= sizeof (BLOCK) + MALLOC_ALIGNMENT)
            {
                BLOCK *new_free;

                new_free =
                    (BLOCK *)((uint8_t *)block
                              + sizeof (BLOCK)
                              + required);

                new_free->size = remaining - sizeof (BLOCK);
                new_free->next = next->next;

                if (previous)
                    previous->next = new_free;
                else
                    man.free_blocks = new_free;
            }
            else
            {
                /*
                 * Consume the entire neighboring block.
                 */
                if (previous)
                    previous->next = next->next;
                else
                    man.free_blocks = next->next;
            }

            block->size = required;
            return ptr;
        }
    }


    /*
     * Couldn't grow in place.
     */
    {
        void *newptr;

        newptr = malloc (newsize);

        if (!newptr)
            return NULL;

        memcpy (newptr, ptr, oldsize);
        free (ptr);

        return newptr;
    }
}


/*
 * Allocate zeroed memory.
 */
void *
calloc (size_t count, size_t size)
{
    size_t total;
    void *ptr;

    /*
     * Detect count * size overflow.
     */
    if (size != 0 && count > SIZE_MAX / size)
        return NULL;

    total = count * size;

    ptr = malloc (total);

    if (!ptr)
        return NULL;

    memset (ptr, 0, total);

    return ptr;
}