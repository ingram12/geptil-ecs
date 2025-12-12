/* Simple arena allocator with automatic growth using realloc
 * Provides fast bump allocation and expands the backing buffer
 * with realloc when there isn't enough space.
 */
#ifndef GEPTIL_MEMORY_ARENA_H
#define GEPTIL_MEMORY_ARENA_H

#include <stddef.h>

typedef struct Arena {
    unsigned char *buffer; /* owned buffer */
    size_t capacity;       /* total bytes allocated */
    size_t used;           /* bytes used */
} Arena;

/* Initialize arena. If initial_capacity == 0 a sensible default is used. */
void arena_init(Arena *a, size_t initial_capacity);

/* Allocate `size` bytes from the arena (no zeroing). Returns NULL on OOM. */
void *arena_alloc(Arena *a, size_t size);

void *arena_realloc(Arena *a, void *ptr, size_t old_size, size_t new_size);

/* Allocate `size` bytes with `alignment` (power-of-two). */
void *arena_alloc_align(Arena *a, size_t size, size_t alignment);

/* Reset arena to empty (does not free buffer). Use to reuse memory. */
void arena_reset(Arena *a);

/* Free arena buffer (makes arena unusable until reinitialized). */
void arena_destroy(Arena *a);

/* Convenience: current used bytes */
size_t arena_used(const Arena *a);

#endif /* GEPTIL_MEMORY_ARENA_H */
