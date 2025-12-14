#pragma once

#include "memory/arena.h"
#include "ecs/ecs.h"

typedef struct Context {
    Ecs ecs;
    Arena arena;
} Context;

void geptil_init_context(Context *context);
void geptil_destroy_context(Context* context);
