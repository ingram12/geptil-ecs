#pragma once

#include "memory/arena.h"
#include "ecs/ecs.h"
#include "vulkan/vulkan_context.h"

typedef struct Geptil_Context {
    Geptil_Ecs ecs;
    Geptil_Arena arena;
    Geptil_VulkanContext vulkan;
} Geptil_Context;

void geptil_init_context(Geptil_Context *context);
void geptil_destroy_context(Geptil_Context* context);
