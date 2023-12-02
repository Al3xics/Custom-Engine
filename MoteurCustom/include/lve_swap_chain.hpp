#pragma once

#include "lve_device.hpp"

// vulkan headers
#include <vulkan/vulkan.h>

// std lib headers
#include <memory>
#include <string>
#include <vector>

namespace lve {
    /**
     * @brief Represents a Vulkan swap chain for handling image presentation.
    */
    class LveSwapChain {
    public:
        /** @brief Maximum number of frames in flight. */
        static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

        /**
         * @brief Constructs an LveSwapChain object.
         * @param deviceRef : Reference to the LveDevice used for Vulkan operations.
         * @param windowExtent : The extent (width and height) of the window.
        */
        LveSwapChain(LveDevice& deviceRef, VkExtent2D windowExtent);

        /**
         * @brief Constructs an LveSwapChain object based on a previous swap chain (used for handling window resizing).
         * @param deviceRef : Reference to the LveDevice used for Vulkan operations.
         * @param windowExtent : The extent (width and height) of the window.
         * @param previous : A shared pointer to the previous swap chain.
        */
        LveSwapChain(LveDevice& deviceRef, VkExtent2D windowExtent, std::shared_ptr<LveSwapChain>previous);
        
        /**
         * @brief Destructor for LveSwapChain, releasing associated resources.
        */
        ~LveSwapChain();

        LveSwapChain(const LveSwapChain&) = delete;
        LveSwapChain& operator=(const LveSwapChain&) = delete;

        /**
         * @brief Gets the frame buffer at the specified index.
         * @param index : The index of the frame buffer.
         * @return The Vulkan frame buffer.
        */
        VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }

        /**
         * @brief Gets the Vulkan render pass.
         * @return The Vulkan render pass.
        */
        VkRenderPass getRenderPass() { return renderPass; }

        /**
         * @brief Gets the image view at the specified index.
         * @param index : The index of the image view.
         * @return The Vulkan image view.
        */
        VkImageView getImageView(int index) { return swapChainImageViews[index]; }

        /**
         * @brief Gets the number of images in the swap chain.
         * @return The number of images.
        */
        size_t imageCount() { return swapChainImages.size(); }

        /**
         * @brief Gets the image format of the swap chain.
         * @return The Vulkan image format.
        */
        VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }

        /**
         * @brief Gets the extent of the swap chain.
         * @return The Vulkan extent.
        */
        VkExtent2D getSwapChainExtent() { return swapChainExtent; }

        /**
         * @brief Gets the width of the swap chain extent.
         * @return The width.
        */
        uint32_t width() { return swapChainExtent.width; }

        /**
         * @brief Gets the height of the swap chain extent.
         * @return The height.
        */
        uint32_t height() { return swapChainExtent.height; }

        /**
         * @brief Gets the aspect ratio of the swap chain extent.
         * @return The aspect ratio.
        */
        float extentAspectRatio() { return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height); }

        /**
         * @brief Compares swap formats between two swap chains.
         * @param swapChain : The other swap chain.
         * @return True if the swap formats match, false otherwise.
        */
        bool compareSwapFormats(const LveSwapChain& swapChain) const { return swapChain.swapChainDepthFormat == swapChainDepthFormat && swapChain.swapChainImageFormat == swapChainImageFormat; }

        /**
         * @brief Finds the supported depth format.
         * @return The Vulkan depth format.
        */
        VkFormat findDepthFormat();

        /**
         * @brief Acquires the index of the next image for rendering in the swap chain.
         * @param imageIndex : Pointer to store the acquired image index.
         * @return The Vulkan result.
        */
        VkResult acquireNextImage(uint32_t* imageIndex);

        /**
         * @brief Submits command buffers for rendering.
         * @param buffers : The command buffers.
         * @param imageIndex : The index of the image being rendered.
         * @return The Vulkan result.
        */
        VkResult submitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex);


    private:
        /**
         * @brief Initializes the swap chain by calling several private functions.
        */
        void init();

        /**
         * @brief Creates the Vulkan swap chain.
        */
        void createSwapChain();

        /**
         * @brief Creates image views for each image in the swap chain.
        */
        void createImageViews();

        /**
         * @brief Creates depth resources for each image.
        */
        void createDepthResources();

        /**
         * @brief Creates the Vulkan render pass.
        */
        void createRenderPass();

        /**
         * @brief Creates frame buffers for each image.
        */
        void createFramebuffers();

        /**
         * @brief Creates synchronization objects such as semaphores and fences.
        */
        void createSyncObjects();

        /**
         * @brief Chooses the swap surface format for the swap chain.
         * @param availableFormats : The available surface formats.
         * @return The chosen surface format.
        */
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        /**
         * @brief Chooses the swap present mode for the swap chain.
         * @param availablePresentModes : The available present modes.
         * @return The chosen present mode.
        */
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

        /**
         * @brief Chooses the swap extent for the swap chain.
         * @param capabilities : The surface capabilities.
         * @return The chosen swap extent.
        */
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);



        // ----------------- Variable -----------------
        VkFormat swapChainImageFormat; /** @brief The format of the swap chain images. */
        VkFormat swapChainDepthFormat; /** @brief The format of the swap chain depth images. */
        VkExtent2D swapChainExtent; /** @brief The extent of the swap chain. */

        std::vector<VkFramebuffer> swapChainFramebuffers; /** @brief Frame buffers for the swap chain images. */
        VkRenderPass renderPass; /** @brief Vulkan render pass. */

        std::vector<VkImage> depthImages; /** @brief Depth images for each swap chain image. */
        std::vector<VkDeviceMemory> depthImageMemorys; /** @brief Memory for depth images. */
        std::vector<VkImageView> depthImageViews; /** @brief Image views for depth images. */
        std::vector<VkImage> swapChainImages; /** @brief Images in the swap chain. */
        std::vector<VkImageView> swapChainImageViews; /** @brief Image views for swap chain images. */

        LveDevice& device; /** @brief Reference to the LveDevice. */
        VkExtent2D windowExtent; /** @brief The extent of the window. */

        VkSwapchainKHR swapChain; /** @brief Vulkan swap chain. */
        std::shared_ptr<LveSwapChain>oldSwapChain; /** @brief The previous swap chain. */

        std::vector<VkSemaphore> imageAvailableSemaphores; /** @brief Semaphores for image availability. */
        std::vector<VkSemaphore> renderFinishedSemaphores; /** @brief Semaphores for rendering completion. */
        std::vector<VkFence> inFlightFences; /** @brief Fences for in-flight frames. */
        std::vector<VkFence> imagesInFlight; /** @brief Fences for images in flight. */
        size_t currentFrame = 0; /** @brief Index of the current frame. */
    };

}  // namespace lve