#pragma once

#include "../vulkan_context.h"

VkResult create_swapchain(Geptil_VulkanContext* ctx, u32 width, u32 height);
VkResult recreate_swapchain(Geptil_VulkanContext* ctx);
