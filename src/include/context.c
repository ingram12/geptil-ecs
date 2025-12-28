#include "context.h"
#include "logger/logger.h"
#include "vulkan/vulkan_init.h"
#include <GLFW/glfw3.h>

void geptil_init_context(Geptil_Context *context)
{
    if (!context) {
        LOG_FATAL("Context pointer is NULL");
    };

    geptil_arena_init(&context->arena, 1024 * 1024 * 10); // 10 MB
    geptil_init_ecs(&context->arena, &context->ecs);

        // Cube vertices: position (x,y,z) and color (r,g,b)
    static Vertex vertices[] = {
        // Front face
        { {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f} },  // 0
        { { 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f} },  // 1
        { { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f} },  // 2
        { {-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f} },  // 3
        // Back face
        { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f} },  // 4
        { { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f} },  // 5
        { { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f} },  // 6
        { {-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f} },  // 7
    };

    // Cube indices for triangles
    static u32 indices[] = {
        // Front
        0, 1, 2,  2, 3, 0,
        // Right
        1, 5, 6,  6, 2, 1,
        // Back
        7, 6, 5,  5, 4, 7,
        // Left
        4, 0, 3,  3, 7, 4,
        // Bottom
        4, 5, 1,  1, 0, 4,
        // Top
        3, 2, 6,  6, 7, 3,
    };

    Geptil_VulkanContext* vk_ctx = &context->vulkan;
    vk_ctx->vertices = vertices;
    vk_ctx->vertices_size = sizeof(vertices) / sizeof(Vertex);
    vk_ctx->indices = indices;
    vk_ctx->indices_size = sizeof(indices) / sizeof(u32);

    init_vulkan(vk_ctx, "geptil", "geptil engine", 800, 600);
}

void geptil_destroy_context(Geptil_Context *context)
{
    if (!context)
        return;
    geptil_arena_destroy(&context->arena);
}

void geptil_time_update(Geptil_Context *context)
{
    if (!context) return;

    double now = glfwGetTime();
    Geptil_Time *t = &context->time;

    // On first call, initialize last tick to current time.
    if (t->_last_ticks == 0.0) {
        t->_last_ticks = now;
        t->dt = 0.0f;
        // Keep accumulated time and frame index consistent
        // (assumes zero-initialization from context creation).
        return;
    }

    double delta = now - t->_last_ticks;
    t->dt = (float)delta;
    t->time += delta;
    t->frame_index++;
    t->_last_ticks = now;
}
