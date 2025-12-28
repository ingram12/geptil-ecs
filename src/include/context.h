#pragma once

#include "memory/arena.h"
#include "ecs/ecs.h"
#include "vulkan/vulkan_context.h"
#include <stdbool.h>
#include "time/time.h"

typedef struct Geptil_Context {
    Geptil_Ecs ecs;
    Geptil_Arena arena;
    Geptil_VulkanContext vulkan;
    Geptil_Time time;
} Geptil_Context;

void geptil_init_context(Geptil_Context *context);
void geptil_destroy_context(Geptil_Context* context);
