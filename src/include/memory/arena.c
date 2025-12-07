#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "arena.h"
#include "../logger/logger.h"

static inline uintptr_t align_up(uintptr_t ptr, size_t alignment) {
    return (ptr + (alignment - 1)) & ~(alignment - 1);
}

void arena_init(Arena *a, size_t initial_capacity) {
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
    a->grow_size = initial_capacity;
}

static int ensure_capacity(Arena *a, size_t needed) {
	if (a->capacity >= needed) {
        return 0;
    }

    LOG_FATAL("Arena out of memory: needed %zu bytes, but only %zu bytes available", needed, a->capacity - a->used);

	return 1;
}

void *arena_alloc_align(Arena *a, size_t size, size_t alignment) {
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

void *arena_alloc(Arena *a, size_t size) {
	return arena_alloc_align(a, size, sizeof(void *));
}

void arena_reset(Arena *a) {
	if (a == NULL) {
        LOG_FATAL("Arena pointer is NULL");
    }
	a->used = 0;
}

void arena_destroy(Arena *a) {
	if (a == NULL) {
        LOG_FATAL("Arena pointer is NULL");
    }

	free(a->buffer);
	a->buffer = NULL;
	a->capacity = 0;
	a->used = 0;
	a->grow_size = 0;
}

size_t arena_used(const Arena *a) {
	return a ? a->used : 0;
}
