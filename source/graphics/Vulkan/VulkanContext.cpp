#include "VulkanContext.hpp"
#include "GLFWWindow.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vulkan/vulkan_core.h>

void VulkanContext::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = APPLICATION_NAME;
    appInfo.applicationVersion = VK_MAKE_API_VERSION(0, APPLICATION_VERSION_MAJOR,
                                                        APPLICATION_VERSION_MINOR,
                                                        APPLICATION_VERSION_PATCH);
    appInfo.pEngineName = ENGINE_NAME;
    appInfo.engineVersion = VK_MAKE_API_VERSION(0, ENGINE_VERSION_MAJOR,
                                                   ENGINE_VERSION_MINOR,
                                                   ENGINE_VERSION_PATCH);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    VkResult res = vkCreateInstance(&createInfo, nullptr, &(VulkanContext::instance));
    if(res != VK_SUCCESS) printf("failed to create instance!");

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    printf("%i extensions supported\n", extensionCount);
}

uint32_t VulkanContext::getBestFamilyIndex(VkPhysicalDevice device) {
    uint32_t familyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);
    VkQueueFamilyProperties* families = new VkQueueFamilyProperties[familyCount];
    vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, families);

    uint8_t largestScore = 0;
    uint32_t bestIndex = 0;
    for(uint32_t j = 0; j < familyCount; j++) {
        uint8_t familyScore = 0;
        if(families[j].queueFlags & VK_QUEUE_GRAPHICS_BIT) familyScore += 8;
        if(families[j].queueFlags & VK_QUEUE_COMPUTE_BIT) familyScore += 2;
        if(families[j].queueFlags & VK_QUEUE_TRANSFER_BIT) familyScore += 2;
        if(families[j].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) familyScore += 1;
        if(families[j].queueFlags & VK_QUEUE_PROTECTED_BIT) familyScore += 1;
        #ifdef VK_ENABLE_BETA_EXTENSIONS
        if(families[j].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT) familyScore += 2;
        if(families[j].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT) familyScore += 2;
        #endif
        if(familyScore > largestScore) {
            bestIndex = j;
            largestScore = familyScore;
        }
    }

    delete[] families;
    return bestIndex;
}

void VulkanContext::createDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(VulkanContext::instance, &deviceCount, nullptr);
    VkPhysicalDevice* devices = new VkPhysicalDevice[deviceCount];
    vkEnumeratePhysicalDevices(VulkanContext::instance, &deviceCount, devices);

    VulkanContext::gpu = devices[0];
    VulkanContext::familyIndex = VulkanContext::getBestFamilyIndex(VulkanContext::gpu);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = VulkanContext::familyIndex;
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    const char* vkExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createDeviceInfo{};
    createDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createDeviceInfo.pQueueCreateInfos = &queueCreateInfo;
    createDeviceInfo.queueCreateInfoCount = 1;
    createDeviceInfo.pEnabledFeatures = &deviceFeatures;
    createDeviceInfo.enabledLayerCount = 0;
    createDeviceInfo.enabledExtensionCount = 1;
    createDeviceInfo.ppEnabledExtensionNames = &vkExtensions;

    VkResult deviceStatus = vkCreateDevice((VulkanContext::gpu),
                                           &createDeviceInfo,
                                           nullptr,
                                           &(VulkanContext::device));
    if(deviceStatus != VK_SUCCESS) {
        printf("failed to create logical device!");
    }

    vkGetDeviceQueue(VulkanContext::device, VulkanContext::familyIndex, 0, &(VulkanContext::queue));

    delete[] devices;
}

void VulkanContext::createSurface(GLFWwindow* win) {
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(VulkanContext::gpu,
                                         VulkanContext::familyIndex,
                                         VulkanContext::surface, &presentSupport);
    if(!presentSupport) printf("physical device not support window surface!");

    VkResult surfaceStatus = glfwCreateWindowSurface(VulkanContext::instance, win,
                                                     nullptr, &(VulkanContext::surface));
    if(surfaceStatus != VK_SUCCESS) printf("failed to create window surface!");
}

void VulkanContext::createSwapChain() {
    VkSwapchainCreateInfoKHR createSwapChainInfo{};
    createSwapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createSwapChainInfo.surface = VulkanContext::surface;
    createSwapChainInfo.minImageCount = 1;
    createSwapChainInfo.imageFormat = VK_FORMAT_R8G8B8A8_UINT;
    createSwapChainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    createSwapChainInfo.imageExtent = {1024, 768};
    createSwapChainInfo.imageArrayLayers = 1;
    createSwapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createSwapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createSwapChainInfo.queueFamilyIndexCount = 0;
    createSwapChainInfo.pQueueFamilyIndices = nullptr;
    createSwapChainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createSwapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createSwapChainInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
    createSwapChainInfo.clipped = VK_TRUE;
    createSwapChainInfo.oldSwapchain = VK_NULL_HANDLE;

    VkResult swapStatus = vkCreateSwapchainKHR(VulkanContext::device, &createSwapChainInfo,
                                               nullptr, &(VulkanContext::swapChain));
    if(swapStatus != VK_SUCCESS) printf("failed to create swap chain!");

    VkImage swapChainImage;
    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(VulkanContext::device, 
                            VulkanContext::swapChain, &imageCount, nullptr);
    vkGetSwapchainImagesKHR(VulkanContext::device,
                            VulkanContext::swapChain, &imageCount, &swapChainImage);
    
    VkImageViewCreateInfo createImageViewInfo{};
    createImageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createImageViewInfo.image = swapChainImage;
    createImageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createImageViewInfo.format = VK_FORMAT_R8G8B8A8_UINT;
    createImageViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createImageViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createImageViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createImageViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createImageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createImageViewInfo.subresourceRange.baseMipLevel = 0;
    createImageViewInfo.subresourceRange.levelCount = 1;
    createImageViewInfo.subresourceRange.baseArrayLayer = 0;
    createImageViewInfo.subresourceRange.layerCount = 1;
    VkResult imageViewStatus = vkCreateImageView(VulkanContext::device, &createImageViewInfo,
                                                 nullptr, &(VulkanContext::imageView));
    if(imageViewStatus != VK_SUCCESS) printf("failed to create image view!");

}

void VulkanContext::createRenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = VK_FORMAT_R8G8B8A8_UINT;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    VkResult renderPassStatus = vkCreateRenderPass(VulkanContext::device, &renderPassInfo,
                                                   nullptr, &(VulkanContext::renderPass));
    if(renderPassStatus != VK_SUCCESS) printf("failed to create render pass!");
}

VkShaderModule VulkanContext::createShaderModule(const uint32_t* code, uint32_t size) {
    VkShaderModuleCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.codeSize = size;
    info.pCode = code;

    VkShaderModule module;
    VkResult status = vkCreateShaderModule(VulkanContext::device, &info, nullptr, &module);
    if(status != VK_SUCCESS) printf("failed to create vert shader module!");
    return module;
}

void VulkanContext::createPipeline(uint32_t width, uint32_t height, std::string shaderName) {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0; // Optional
    pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

    VkResult pipelineStatus = vkCreatePipelineLayout(VulkanContext::device, &pipelineLayoutInfo,
                                                     nullptr, &(VulkanContext::pipelineLayout));
    if(pipelineStatus != VK_SUCCESS) printf("failed to create pipeline layout!");

    std::vector<char> vertexShader = VulkanContext::readFile(shaderName + "_vert.spv");
    VkShaderModule vertexShaderModule = VulkanContext::createShaderModule(
            reinterpret_cast<const uint32_t*>(vertexShader.data()), vertexShader.size());
    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertexShaderModule;
    vertShaderStageInfo.pName = "main";

    std::vector<char> fragmentShader = VulkanContext::readFile(shaderName + "_frag.spv");
    VkShaderModule fragmentShaderModule = VulkanContext::createShaderModule(
            reinterpret_cast<const uint32_t*>(fragmentShader.data()), fragmentShader.size());
    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragmentShaderModule;
    fragShaderStageInfo.pName = "main";
    
    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = nullptr;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = nullptr;

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)width;
    viewport.height = (float)height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = {width, height};

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f; // Optional
    rasterizer.depthBiasClamp = 0.0f; // Optional
    rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f; // Optional
    multisampling.pSampleMask = nullptr; // Optional
    multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
    multisampling.alphaToOneEnable = VK_FALSE; // Optional

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
        VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f; // Optional
    colorBlending.blendConstants[1] = 0.0f; // Optional
    colorBlending.blendConstants[2] = 0.0f; // Optional
    colorBlending.blendConstants[3] = 0.0f; // Optional

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr; // Optional
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = nullptr; // Optional
    pipelineInfo.layout = pipelineLayout;
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
    pipelineInfo.basePipelineIndex = -1; // Optional
    
    VkResult gfxPipeStatus = vkCreateGraphicsPipelines(VulkanContext::device, VK_NULL_HANDLE,
                                                       1, &pipelineInfo, nullptr,
                                                       &(VulkanContext::pipeline));
    if(gfxPipeStatus != VK_SUCCESS) printf("failed to create graphics pipeline!");

    vkDestroyShaderModule(VulkanContext::device, vertexShaderModule, nullptr);
    vkDestroyShaderModule(VulkanContext::device, fragmentShaderModule, nullptr);
}

std::vector<char> VulkanContext::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    } 

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

void VulkanContext::createFramebuffer(uint32_t width, uint32_t height) {
    VkImageView attachments[] = { VulkanContext::imageView };
    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = 1024;
    framebufferInfo.height = 768;
    framebufferInfo.layers = 1;
    
    VkResult framebufferStatus = vkCreateFramebuffer(VulkanContext::device, &framebufferInfo,
                                                     nullptr, &(VulkanContext::framebuffer));
    if(framebufferStatus != VK_SUCCESS) printf("failed to create framebuffer!");
}

void VulkanContext::createCommandBuffer() {
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = VulkanContext::familyIndex;

    VkResult cmdPoolStatus = vkCreateCommandPool(VulkanContext::device, &poolInfo,
                                                 nullptr, &(VulkanContext::commandPool));
    if(cmdPoolStatus != VK_SUCCESS) printf("failed to create command pool!");

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    VkResult cmdBufferStatus = vkAllocateCommandBuffers(VulkanContext::device, &allocInfo,
                                                        &(VulkanContext::commandBuffer));
    if(cmdBufferStatus != VK_SUCCESS) printf("failed to allocate command buffers!");

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    VkResult cmdStart = vkBeginCommandBuffer(VulkanContext::commandBuffer, &beginInfo);
    if(cmdStart != VK_SUCCESS) printf("failed to begin recording command buffer!");
}

void VulkanContext::renderPassBegin(uint8_t width, uint8_t height) {
    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = renderPass;
    renderPassBeginInfo.framebuffer = VulkanContext::framebuffer;
    renderPassBeginInfo.renderArea.offset = {0, 0};
    renderPassBeginInfo.renderArea.extent = {1024, 768};
    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(VulkanContext::commandBuffer, &renderPassBeginInfo,
                         VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(VulkanContext::commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      VulkanContext::pipeline);

    vkCmdDraw(VulkanContext::commandBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(VulkanContext::commandBuffer);
    if(vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) printf("failed to record command buffer!");
}

void VulkanContext::createSemaphore() {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT; 

    VkResult imageSStatus = vkCreateSemaphore(VulkanContext::device, &semaphoreInfo,
                                            nullptr, &(VulkanContext::imageSem));
    VkResult renderSStatus = vkCreateSemaphore(VulkanContext::device, &semaphoreInfo,
                                               nullptr, &(VulkanContext::renderSem));
    VkResult fenceStatus = vkCreateFence(VulkanContext::device, &fenceInfo,
                                         nullptr, &(VulkanContext::fence));

    if (imageSStatus != VK_SUCCESS || renderSStatus != VK_SUCCESS || fenceStatus != VK_SUCCESS)
        printf("failed to create semaphores!");
}

void VulkanContext::renderPassInfo() {
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = VulkanContext::renderPass;
    renderPassInfo.framebuffer = VulkanContext::framebuffer;
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = {1024, 768};

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(VulkanContext::commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(VulkanContext::commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      VulkanContext::pipeline);
    vkCmdDraw(VulkanContext::commandBuffer, 3, 1, 0, 0);
    vkCmdEndRenderPass(VulkanContext::commandBuffer);

    if(vkEndCommandBuffer(VulkanContext::commandBuffer) != VK_SUCCESS) 
        printf("failed to record command buffer!");
}

void VulkanContext::run() {
    vkWaitForFences(VulkanContext::device, 1, &(VulkanContext::fence), VK_TRUE, UINT64_MAX);
    vkResetFences(VulkanContext::device, 1, &(VulkanContext::fence));

    uint32_t imageIndex;
    vkAcquireNextImageKHR(VulkanContext::device, VulkanContext::swapChain,
                          UINT64_MAX, VulkanContext::imageSem, VK_NULL_HANDLE, &imageIndex);

    vkResetCommandBuffer(VulkanContext::commandBuffer, /*VkCommandBufferResetFlagBits*/ 0);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(VulkanContext::commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {VulkanContext::imageSem};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &(VulkanContext::commandBuffer);

    VkSemaphore signalSemaphores[] = {VulkanContext::renderSem};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    VkResult qRes = vkQueueSubmit(VulkanContext::queue, 1, &submitInfo, VulkanContext::fence);

    if (qRes != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {VulkanContext::swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(VulkanContext::queue, &presentInfo);
}

VulkanContext::VulkanContext(GLFWwindow* win, uint32_t width,
                             uint32_t height, std::string shaderName) {
    VulkanContext::createInstance();
    VulkanContext::createDevice();
    VulkanContext::createSurface(win);
    VulkanContext::createSwapChain();
    VulkanContext::createRenderPass();
    VulkanContext::createPipeline(width, height, shaderName);
    VulkanContext::createFramebuffer(width, height);
    VulkanContext::createCommandBuffer();
    VulkanContext::renderPassBegin(width, height);
    VulkanContext::createSemaphore();
    VulkanContext::renderPassInfo();
}

VulkanContext::~VulkanContext() {
    vkDestroySemaphore(VulkanContext::device, VulkanContext::imageSem, nullptr);
    vkDestroySemaphore(VulkanContext::device, VulkanContext::renderSem, nullptr);
    vkDestroyFence(VulkanContext::device, VulkanContext::fence, nullptr);
    vkDestroyCommandPool(VulkanContext::device, VulkanContext::commandPool, nullptr);
    vkDestroyFramebuffer(VulkanContext::device, VulkanContext::framebuffer, nullptr);
    vkDestroyPipeline(VulkanContext::device, VulkanContext::pipeline, nullptr);
    vkDestroyPipelineLayout(VulkanContext::device, VulkanContext::pipelineLayout, nullptr);
    vkDestroyRenderPass(VulkanContext::device, VulkanContext::renderPass, nullptr);
    vkDestroyImageView(VulkanContext::device, VulkanContext::imageView, nullptr);
    vkDestroySwapchainKHR(VulkanContext::device, VulkanContext::swapChain, nullptr);
    vkDestroySurfaceKHR(VulkanContext::instance, VulkanContext::surface, nullptr);
    vkDestroyDevice(VulkanContext::device, nullptr);
    vkDestroyInstance(VulkanContext::instance, nullptr);
}

// vim:tabstop=4:shiftwidth=4:expandtab:textwidth=100
