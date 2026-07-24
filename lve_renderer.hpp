#pragma once

#include "lve_window.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
 
#include <cassert>
#include <memory>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace lve
{
    class LveRenderer
    {
        public:
            LveRenderer(LveWindow &window, LveDevice &device);
            ~LveRenderer();
            LveRenderer(const LveRenderer &) = delete;
            LveRenderer &operator=(const LveRenderer &) = delete;

            VkRenderPass getSwapChainRenderPass() const { return lveSwapChain->getRenderPass(); }
            bool isFrameInProgress() const { return isFrameStarted; }

            VkCommandBuffer getCurrentCommandBuffer() const { 
                assert(isFrameStarted && "cannot get command buffer when frame is not started");
                return commandBuffers[currentFrameIndex]; 
            }

            int getFrameIndex() const {
                assert(isFrameStarted && "cannot get frame index when frame not in progress");
                return currentFrameIndex;
            }

            VkCommandBuffer beginFrame();
            void endFrame();
            void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
            void enddSwapChainRenderPass(VkCommandBuffer commandBuffer);

        private:
            void createCommandBuffers();
            void freeCommandBuffers();
            void recreateSwapChain();

            LveWindow &lveWindow;
            LveDevice &lveDevice;
            std::unique_ptr<LveSwapChain> lveSwapChain;
            std::vector<VkCommandBuffer> commandBuffers;

            uint32_t currentImageIndex{0};
            int currentFrameIndex{0};
            bool isFrameStarted{false};
    };
}