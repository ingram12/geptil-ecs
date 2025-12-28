#include "include/context.h"
#include "include/project.h"
#include "include/logger/logger.h"
#include "include/state_init.h"
#include "include/vulkan/vulkan_draw.h"
#include "include/ecs_tick.h"
#include "include/time/time.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    LOG_INFO("Starting %s version %s", PROJECT_NAME, PROJECT_VERSION);

    Geptil_Context ctx = {0};
    geptil_init_context(&ctx);

    geptil_world_init(&ctx);

    Geptil_VulkanContext *vk_ctx = &ctx.vulkan;
    while (!glfwWindowShouldClose(vk_ctx->window)) {
        glfwPollEvents();
        geptil_time_update(&ctx.time);
        geptil_ecs_tick(&ctx);
        draw_frame(vk_ctx);
    }

    return EXIT_SUCCESS;
}
