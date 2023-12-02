#pragma once

#include "lve_window.hpp"

// std lib headers
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace lve {
    /**
     * @brief Structure holding details about swap chain support.
    */
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities; /** @brief Detailed capabilities of the surface. */
        std::vector<VkSurfaceFormatKHR> formats; /** @brief Available surface formats. */
        std::vector<VkPresentModeKHR> presentModes; /** @brief Available presentation modes. */
    };

    /**
     * @brief Structure representing queue family indices.
    */
    struct QueueFamilyIndices {
        uint32_t graphicsFamily = 0; /** @brief Index of the graphics queue family. */
        uint32_t presentFamily = 0; /** @brief Index of the presentation queue family. */
        bool graphicsFamilyHasValue = false; /** @brief Flag indicating if graphics family index is valid. */
        bool presentFamilyHasValue = false; /** @brief Flag indicating if presentation family index is valid. */

        /**
         * @brief Check if both graphics and presentation families have valid indices.
         * @return True if both indices are valid, false otherwise.
        */
        bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
    };

    /**
     * @brief Vulkan device management class.
    */
    class LveDevice {
    public:
        #ifdef NDEBUG
            const bool enableValidationLayers = false; /** @brief Enable Vulkan validation layers flag (Release mode). */
        #else
            const bool enableValidationLayers = true; /** @brief Enable Vulkan validation layers flag (Debug mode). */
        #endif

        /**
         * @brief Constructor for LveDevice.
         * @param window : Reference to the LveWindow instance.
        */
        LveDevice(LveWindow& window);

        /**
         * @brief Destructor for LveDevice.
        */
        ~LveDevice();

        LveDevice(const LveDevice&) = delete;
        LveDevice& operator=(const LveDevice&) = delete;
        LveDevice(LveDevice&&) = delete;
        LveDevice& operator=(LveDevice&&) = delete;

        /**
         * @brief Get Vulkan instance.
         * @return Vulkan instance handle.
        */
        VkInstance getInstance() const { return instance; }

        /**
         * @brief Get Vulkan physical device.
         * @return Vulkan physical device handle.
        */
        VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }

        /**
         * @brief Get Vulkan command pool.
         * @return Vulkan command pool handle.
        */
        VkCommandPool getCommandPool() const { return commandPool; }

        /**
         * @brief Get Vulkan logical device.
         * @return Vulkan logical device handle.
        */
        VkDevice getDevice() const { return device_; }

        /**
         * @brief Get Vulkan surface.
         * @return Vulkan surface handle.
        */
        VkSurfaceKHR getSurface() const { return surface_; }

        /**
         * @brief Get Vulkan graphics queue.
         * @return Vulkan graphics queue handle.
        */
        VkQueue getGraphicsQueue() const { return graphicsQueue_; }

        /**
         * @brief Get Vulkan presentation queue.
         * @return Vulkan presentation queue handle.
        */
        VkQueue getPresentQueue() const { return presentQueue_; }

        /**
         * @brief Get graphics queue family index.
         * @return Graphics queue family index.
        */
        static uint32_t getGraphicsQueueFamily() { QueueFamilyIndices indice; return indice.graphicsFamily; }

        /**
         * @brief Get details about swap chain support.
         * @return SwapChainSupportDetails structure.
        */
        SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }

        /**
         * @brief Find memory type based on type filter and properties.
         * @param typeFilter : Type filter.
         * @param properties : Memory properties.
         * @return Memory type index.
        */
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        /**
         * @brief Find physical queue families for the device.
         * @return QueueFamilyIndices structure.
        */
        QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }

        /**
         * @brief Find a supported format from a list of candidates.
         * @param candidates : List of candidate formats.
         * @param tiling : Image tiling mode.
         * @param features : Format feature flags.
         * @return Supported Vulkan format.
        */
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        /**
         * @brief Create a Vulkan buffer.
         * @param size : Size of the buffer.
         * @param usage : Buffer usage flags.
         * @param properties : Memory properties flags.
         * @param buffer : Output parameter for Vulkan buffer handle.
         * @param bufferMemory : Output parameter for Vulkan buffer memory handle.
        */
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        
        /**
         * @brief Begin a single time command.
         * @return Vulkan command buffer handle.
        */
        VkCommandBuffer beginSingleTimeCommands();

        /**
         * @brief End a single time command.
         * @param commandBuffer : Vulkan command buffer handle.
        */
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        /**
         * @brief Copy data from one Vulkan buffer to another.
         * @param srcBuffer : Source Vulkan buffer.
         * @param dstBuffer : Destination Vulkan buffer.
         * @param size : Size of the data to be copied.
        */
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        /**
         * @brief Copy data from a Vulkan buffer to a Vulkan image.
         * @param buffer : Source Vulkan buffer.
         * @param image : Destination Vulkan image.
         * @param width : Width of the image.
         * @param height : Height of the image.
         * @param layerCount : Number of layers in the image.
        */
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

        /**
         * @brief Create a Vulkan image with specified information.
         * @param imageInfo : Vulkan image creation information.
         * @param properties : Memory properties flags.
         * @param image : Output parameter for Vulkan image handle.
         * @param imageMemory : Output parameter for Vulkan image memory handle.
        */
        void createImageWithInfo(const VkImageCreateInfo& imageInfo, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);



        // ----------------- Variable -----------------
        VkPhysicalDeviceProperties properties; /** @brief Vulkan physical device properties. */


    private:
        /**
         * @brief Create Vulkan instance.
        */
        void createInstance();

        /**
         * @brief Setup Vulkan debug messenger.
        */
        void setupDebugMessenger();

        /**
         * @brief Create Vulkan surface.
        */
        void createSurface();

        /**
         * @brief Pick a suitable Vulkan physical device.
        */
        void pickPhysicalDevice();

        /**
         * @brief Create Vulkan logical device.
        */
        void createLogicalDevice();

        /**
         * @brief Create Vulkan command pool.
        */
        void createCommandPool();

        /**
         * @brief Check if the physical device is suitable for the application.
         * @param device : Vulkan physical device handle.
         * @return True if the device is suitable, false otherwise.
        */
        bool isDeviceSuitable(VkPhysicalDevice device);

        /**
         * @brief Get the list of required Vulkan extensions.
         * @return List of required Vulkan extensions.
        */
        std::vector<const char*> getRequiredExtensions();

        /**
         * @brief Check if the required validation layers are supported.
         * @return True if all validation layers are supported, false otherwise.
        */
        bool checkValidationLayerSupport();

        /**
         * @brief Find queue families supported by the physical device.
         * @param device : Vulkan physical device.
         * @return QueueFamilyIndices structure.
        */
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        /**
         * @brief Populate the Vulkan debug messenger create info structure.
         * @param createInfo : Vulkan debug messenger create info structure to be populated.
        */
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        /**
         * @brief Check if GLFW has the required instance extensions.
        */
        void hasGflwRequiredInstanceExtensions();

        /**
         * @brief Check if the physical device supports the required device extensions.
         * @param device : Vulkan physical device handle.
         * @return True if all required extensions are supported, false otherwise.
        */
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        /**
         * @brief Query swap chain support details for a given physical device.
         * @param device : Vulkan physical device.
         * @return SwapChainSupportDetails structure.
        */
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);



        // ----------------- Variable -----------------
        VkInstance instance; /** @brief Vulkan instance handle. */
        VkDebugUtilsMessengerEXT debugMessenger; /** @brief Vulkan debug messenger handle. */
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; /** @brief Vulkan physical device handle. */
        LveWindow& window; /** @brief Reference to the LveWindow instance. */
        VkCommandPool commandPool; /** @brief Vulkan command pool handle. */

        VkDevice device_; /** @brief Vulkan logical device handle. */
        VkSurfaceKHR surface_; /** @brief Vulkan surface handle. */
        VkQueue graphicsQueue_; /** @brief Vulkan graphics queue handle. */
        VkQueue presentQueue_; /** @brief Vulkan presentation queue handle. */

        const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" }; /** @brief List of validation layers to enable. */
        const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME }; /** @brief List of required device extensions. */
    };

}  // namespace lve