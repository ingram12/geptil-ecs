#pragma once

#include <vulkan/vulkan.h>
#include "../../core_types.h"

VkResult load_shader_code(const char* filename, u32** code, size_t* codeSize);
