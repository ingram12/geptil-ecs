#pragma once

#include "../vulkan_context.h"

VkResult create_sync_objects(Geptil_VulkanContext* ctx);
void cleanup_sync_objects(Geptil_VulkanContext* ctx);
