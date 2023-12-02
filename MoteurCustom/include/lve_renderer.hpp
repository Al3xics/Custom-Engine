#pragma once

#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include "lve_window.hpp"


//std
#include<cassert>
#include <memory>
#include <vector>

namespace lve {
    /**
     * @brief Represents the renderer for Vulkan-based rendering.
    */
    class LveRenderer {
    public:
        /**
         * @brief Constructs an LveRenderer.
         * @param window : The LveWindow reference.
         * @param device : The LveDevice reference.
        */
        LveRenderer(LveWindow& window, LveDevice& device);

        /**
         * @brief Destructor to release associated resources.
        */
        ~LveRenderer();

        LveRenderer(const LveRenderer&) = delete;
        LveRenderer& operator=(const LveRenderer&) = delete;

        /**
         * @brief Gets the Vulkan render pass associated with the swap chain.
         * @return The Vulkan render pass.
        */
        VkRenderPass getSwapChainRenderPass() const { return lveSwapChain->getRenderPass(); }

        /**
         * @brief Gets the aspect ratio of the swap chain.
         * @return The aspect ratio.
        */
        float getAspectRatio() const { return lveSwapChain->extentAspectRatio(); }

        /**
         * @brief Checks if a frame is currently in progress.
         * @return True if a frame is in progress, false otherwise.
        */
        bool isFrameInProgres() const { return isFrameStarted; }

        /**
         * @brief Gets the current command buffer.
         * @return The current command buffer.
        */
        VkCommandBuffer getCurrentCommandBuffer() const { assert(isFrameStarted && "Cannot get command buffer when frame not in progress"); return commandBuffers[currentFrameIndex]; }
        
        /**
         * @brief Gets the index of the current frame.
         * @return The index of the current frame.
        */
        int getFrameIndex()const { assert(isFrameStarted && "Cannot get frame index when frame not in progress"); return currentFrameIndex; }

        /**
         * @brief Begins a new frame, acquiring the next image from the swap chain.
         * @return The command buffer for the current frame.
        */
        VkCommandBuffer beginFrame();

        /**
         * @brief Ends the current frame, submitting commands to the GPU.
        */
        void endFrame();

        /**
         * @brief Begins the render pass for the current swap chain image.
         * @param commandBuffer : The Vulkan command buffer.
        */
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);

        /**
         * @brief Ends the render pass for the current swap chain image.
         * @param commandBuffer : The Vulkan command buffer.
        */
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);


    private:
        /**
         * @brief Creates the Vulkan command buffers.
        */
        void createCommandBuffers();

        /**
         * @brief Frees the Vulkan command buffers.
        */
        void freeCommandBuffers();

        /**
         * @brief Recreates the Vulkan swap chain.
        */
        void recreateSwapChain();



        // ----------------- Variable -----------------
        LveWindow& lveWindow; /** @brief Reference to the LveWindow. */
        LveDevice& lveDevice; /** @brief Reference to the LveDevice. */
        std::unique_ptr<LveSwapChain> lveSwapChain; /** @brief Unique pointer to LveSwapChain. */
        std::vector<VkCommandBuffer> commandBuffers; /** @brief Vector of Vulkan command buffers. */

        uint32_t currentImageIndex; /** @brief Current index of the swap chain image. */
        int currentFrameIndex; /** @brief Current index of the frame. */
        bool isFrameStarted; /** @brief Flag indicating whether a frame is in progress. */
    };
}