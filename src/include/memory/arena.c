#include <stdlib.h>
#include <string.h>
#include "arena.h"
#include "../logger/logger.h"

static inline uintptr_t align_up(uintptr_t ptr, size_t alignment) {
    return (ptr + (alignment - 1)) & ~(alignment - 1);
}

void geptil_arena_init(Arena *a, size_t initial_capacity) {
	if (a == NULL) {
        LOG_FATAL("Arena pointer is NULL");
    }

    if (initial_capacity == 0) {
        LOG_FATAL("Initial capacity must be greater than zero");
    }

	a->buffer = NULL;
	a->used = 0;

    a->buffer = (unsigned char *)malloc(initial_capacity);
    if (!a->buffer) {
        LOG_FATAL("Failed to allocate initial arena buffer of size %zu", initial_capacity);
    }

    a->capacity = initial_capacity;
}

static int ensure_capacity(Arena *a, size_t needed) {
	if (a->capacity >= needed) {
        return 0;
    }

    LOG_FATAL("Arena out of memory: needed %zu bytes, but only %zu bytes available", needed, a->capacity - a->used);

	return 1;
}

void *geptil_arena_alloc_align(Arena *a, size_t size, size_t alignment) {
    if (a == NULL) {
        LOG_FATAL("Arena pointer is NULL");
    }

    if (alignment == 0) alignment = sizeof(void *);

    uintptr_t base = (uintptr_t)a->buffer + a->used;
    uintptr_t aligned = align_up(base, alignment);
    size_t padding = aligned - base;
    size_t total = padding + size;

    ensure_capacity(a, a->used + total);

    void *ptr = (void *)aligned;
    a->used += total;
    return ptr;
}

void *geptil_arena_alloc(Arena *a, size_t size) {
	return geptil_arena_alloc_align(a, size, sizeof(void *));
}

void *geptil_arena_realloc(Arena *a, void *ptr, size_t old_size, size_t new_size) {
    if (!a) {
        LOG_FATAL("Arena pointer is NULL");
    }

    if (!ptr) {
        return geptil_arena_alloc(a, new_size);
    }

    uintptr_t base = (uintptr_t)a->buffer;
    uintptr_t p = (uintptr_t)ptr;

    if (p < base || p >= base + a->used) {
        LOG_FATAL("Pointer to realloc is out of arena bounds");
    }

    // Case 1 — block is last in arena (fast path)
    if (p + old_size == base + a->used) {
        if (new_size > old_size) {
            size_t grow = new_size - old_size;
            ensure_capacity(a, a->used + grow);
            a->used += grow;
        } else {
            size_t shrink = old_size - new_size;
            a->used -= shrink;
        }
        return ptr;
    }

    // Case 2 — must copy
    void *new_ptr = geptil_arena_alloc(a, new_size);
    memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    return new_ptr;
}

void geptil_arena_reset(Arena *a) {
	if (a == NULL) {
        LOG_FATAL("Arena pointer is NULL");
    }
	a->used = 0;
}

void geptil_arena_destroy(Arena *a) {
	if (a == NULL) {
        LOG_FATAL("Arena pointer is NULL");
    }

	free(a->buffer);
	a->buffer = NULL;
	a->capacity = 0;
	a->used = 0;
}

size_t geptil_arena_used(const Arena *a) {
	return a ? a->used : 0;
}
