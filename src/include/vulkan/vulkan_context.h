#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "../core_types.h"

typedef struct {
    u32 graphicsFamily;
} QueueFamilyIndices;

typedef struct Vertex {
    float pos[3];
    float color[3];
} Vertex;

typedef struct {
    u32 width;
    u32 height;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapchain;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    u32 imageCount;
    VkImage* swapchainImages;
    VkImageView* swapchainImageViews;
    VkFramebuffer* swapchainFramebuffers;
    QueueFamilyIndices queueFamilyIndices;
    u32 graphicsQueueFamily;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkCommandPool commandPool;
    VkCommandBuffer* commandBuffers;
    GLFWwindow* window;

    VkSemaphore* imageAvailableSemaphores;
    VkSemaphore* renderFinishedSemaphores;
    VkFence* inFlightFences;
    u32 maxFramesInFlight;
    u32 currentFrame;

    int vertices_size;
    Vertex* vertices;
    int indices_size;
    u32* indices;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
} Geptil_VulkanContext;
