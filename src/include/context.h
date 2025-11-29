#pragma once

#include <stddef.h>
#include <stdint.h>
#include "memory/arena.h"
#include "ecs/ecs.h"

typedef struct Context {
    Ecs* ecs;
    Arena arena;
} Context;

Context* create_context(uint16_t max_components_count);
void destroy_context(Context* context);
