#pragma once

#include "../vulkan_context.h"

VkResult create_command_buffers(Geptil_VulkanContext* ctx);
void cleanup_command_buffers(Geptil_VulkanContext* ctx);
