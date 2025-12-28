#include "vulkan_vertex_buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

u32 findMemoryType(Geptil_VulkanContext* ctx, u32 typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(ctx->physicalDevice, &memProperties);

    for (u32 i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    printf("failed to find suitable memory type!");
    return 0;
}

VkCommandBuffer beginSingleTimeCommands(Geptil_VulkanContext* ctx) {
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = ctx->commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(ctx->device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void endSingleTimeCommands(Geptil_VulkanContext* ctx, VkCommandBuffer commandBuffer) {
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(ctx->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(ctx->graphicsQueue);

    vkFreeCommandBuffers(ctx->device, ctx->commandPool, 1, &commandBuffer);
}

void copyBuffer(Geptil_VulkanContext* ctx, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands(ctx);

    VkBufferCopy copyRegion = {};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    endSingleTimeCommands(ctx, commandBuffer);
}

void createBuffer(
    Geptil_VulkanContext* ctx,
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkBuffer* buffer,
    VkDeviceMemory* bufferMemory
) {
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(ctx->device, &bufferInfo, NULL, buffer) != VK_SUCCESS) {
        printf("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(ctx->device, *buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(ctx, memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(ctx->device, &allocInfo, NULL, bufferMemory) != VK_SUCCESS) {
        printf("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(ctx->device, *buffer, *bufferMemory, 0);
}

void createVertexBuffer(Geptil_VulkanContext* ctx) {
    VkDeviceSize bufferSize = sizeof(ctx->vertices[0]) * ctx->vertices_size;

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(
        ctx,
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        &stagingBuffer,
        &stagingBufferMemory
    );

    void* data;
    vkMapMemory(ctx->device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, ctx->vertices, (size_t) bufferSize);
    vkUnmapMemory(ctx->device, stagingBufferMemory);

    createBuffer(
        ctx,
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        &ctx->vertexBuffer,
        &ctx->vertexBufferMemory
    );

    copyBuffer(ctx, stagingBuffer, ctx->vertexBuffer, bufferSize);

    vkDestroyBuffer(ctx->device, stagingBuffer, NULL);
    vkFreeMemory(ctx->device, stagingBufferMemory, NULL);
}

void createIndexBuffer(Geptil_VulkanContext* ctx) {
    VkDeviceSize bufferSize = sizeof(ctx->indices[0]) * ctx->indices_size;

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    createBuffer(
        ctx,
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        &stagingBuffer,
        &stagingBufferMemory
    );

    void* data;
    vkMapMemory(ctx->device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, ctx->indices, (size_t) bufferSize);
    vkUnmapMemory(ctx->device, stagingBufferMemory);

    createBuffer(
        ctx,
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        &ctx->indexBuffer,
        &ctx->indexBufferMemory
    );

    copyBuffer(ctx,stagingBuffer, ctx->indexBuffer, bufferSize);

    vkDestroyBuffer(ctx->device, stagingBuffer, NULL);
    vkFreeMemory(ctx->device, stagingBufferMemory, NULL);
}
