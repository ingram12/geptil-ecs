#pragma once

#include "memory/arena.h"
#include "ecs/ecs.h"

typedef struct Context {
    Ecs ecs;
    Arena arena;
} Context;

void init_context(Context *context);
void destroy_context(Context* context);
