#ifndef VULKANCONTEXT_HPP
#define VULKANCONTEXT_HPP

#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <vector>

class VulkanContext {
private:
    VkInstance instance;
    VkPhysicalDevice gpu;
    VkDevice device;
    VkQueue queue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    VkImageView imageView;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline pipeline;
    VkFramebuffer framebuffer;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkSemaphore renderSem;
    VkSemaphore imageSem;
    VkFence fence;
    uint32_t familyIndex;

    std::vector<char> readFile(const std::string& filename);

    uint32_t getBestFamilyIndex(VkPhysicalDevice device);
    VkShaderModule createShaderModule(const uint32_t* code, uint32_t size);

    void createInstance();
    void createDevice();
    void createSurface(GLFWwindow* win);
    void createSwapChain();
    void createRenderPass();
    void createPipeline(uint32_t width, uint32_t height, std::string shaderName);
    void createFramebuffer(uint32_t width, uint32_t height);
    void createCommandBuffer();
    void renderPassBegin(uint8_t width, uint8_t height);
    void createSemaphore();
    void renderPassInfo();

public:
    VulkanContext(GLFWwindow* win, uint32_t width, uint32_t height, std::string shaderName);
    ~VulkanContext();

    void run();
};

#endif//VULKANCONTEXT_HPP

// vim:tabstop=4:shiftwidth=4:expandtab:textwidth=100
