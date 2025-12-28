#pragma once

#include "../vulkan_context.h"

VkResult select_physical_device(Geptil_VulkanContext* ctx);
VkResult create_logical_device(Geptil_VulkanContext* ctx);
