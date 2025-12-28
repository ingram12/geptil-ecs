#pragma once

#include "memory/arena.h"
#include "ecs/ecs.h"
#include "vulkan/vulkan_context.h"

typedef struct {
    f32 dt;
    f64 time;
    f64 _last_ticks;
    u64 frame_index;
} Geptil_Time;

typedef struct Geptil_Context {
    Geptil_Ecs ecs;
    Geptil_Arena arena;
    Geptil_VulkanContext vulkan;
    Geptil_Time time;
} Geptil_Context;

void geptil_init_context(Geptil_Context *context);
void geptil_destroy_context(Geptil_Context* context);

// Updates `context->time` using GLFW's high-resolution timer.
void geptil_time_update(Geptil_Context *context);
