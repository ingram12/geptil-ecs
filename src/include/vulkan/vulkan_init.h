#pragma once

#include "vulkan_context.h"

VkResult init_vulkan(
    Geptil_VulkanContext* ctx,
    const char* appName,
    const char* engineName,
    u32 width,
    u32 height
);
