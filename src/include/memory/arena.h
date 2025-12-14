#pragma once

#include <stddef.h>

typedef struct Arena {
    unsigned char *buffer; /* owned buffer */
    size_t capacity;       /* total bytes allocated */
    size_t used;           /* bytes used */
} Arena;

/* Initialize arena. If initial_capacity == 0 a sensible default is used. */
void geptil_arena_init(Arena *a, size_t initial_capacity);

/* Allocate `size` bytes from the arena (no zeroing). Returns NULL on OOM. */
void *geptil_arena_alloc(Arena *a, size_t size);

void *geptil_arena_realloc(Arena *a, void *ptr, size_t old_size, size_t new_size);

/* Allocate `size` bytes with `alignment` (power-of-two). */
void *geptil_arena_alloc_align(Arena *a, size_t size, size_t alignment);

/* Reset arena to empty (does not free buffer). Use to reuse memory. */
void geptil_arena_reset(Arena *a);

/* Free arena buffer (makes arena unusable until reinitialized). */
void geptil_arena_destroy(Arena *a);

/* Convenience: current used bytes */
size_t geptil_arena_used(const Arena *a);
