#pragma once

#include "lve_device.hpp"

namespace lve {
    /**
     * @brief Represents a buffer used in Vulkan rendering.
    */
    class LveBuffer {
    public:
        /**
         * @brief Constructor for LveBuffer.
         * @param device : The Vulkan logical device.
         * @param instanceSize : The size of each instance in the buffer.
         * @param instanceCount : The number of instances in the buffer.
         * @param usageFlags : Vulkan buffer usage flags.
         * @param memoryPropertyFlags : Vulkan memory property flags.
         * @param minOffsetAlignment : Minimum alignment requirement for offsets.
        */
        LveBuffer( LveDevice& device, VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment = 1); 
        
        /**
         * @brief Destructor for LveBuffer.
        */
        ~LveBuffer();

        LveBuffer(const LveBuffer&) = delete;
        LveBuffer& operator=(const LveBuffer&) = delete;

        /**
         * @brief Maps the buffer memory.
         * @param size : The size of the memory to map.
         * @param offset : The offset from the beginning of the buffer.
         * @return Result of the memory mapping operation.
        */
        VkResult map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
        
        /**
         * @brief Unmaps the buffer memory.
        */
        void unmap();

        /**
         * @brief Writes data to the buffer.
         * @param data : The data to be written.
         * @param size : The size of the data to be written.
         * @param offset : The offset from the beginning of the buffer.
        */
        void writeToBuffer(void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
        
        /**
         * @brief Flushes the mapped memory ranges.
         * @param size : The size of the memory to flush.
         * @param offset : The offset from the beginning of the buffer.
         * @return Result of the flush operation.
        */
        VkResult flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

        /**
         * @brief Gets the descriptor buffer information for the buffer.
         * @param size : The size of the memory in the descriptor.
         * @param offset : The offset from the beginning of the buffer.
         * @return Descriptor buffer information.
        */
        VkDescriptorBufferInfo descriptorInfo(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);
        
        /**
         * @brief Invalidates the mapped memory ranges.
         * @param size : The size of the memory to invalidate.
         * @param offset : The offset from the beginning of the buffer.
         * @return Result of the invalidate operation.
        */
        VkResult invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

        /**
         * @brief Writes data to a specific index in the buffer.
         * @param data : The data to be written.
         * @param index : The index of the instance in the buffer.
        */
        void writeToIndex(void* data, int index);

        /**
         * @brief Flushes the mapped memory range for a specific index.
         * @param index : The index of the instance in the buffer.
         * @return Result of the flush operation.
        */
        VkResult flushIndex(int index);

        /**
         * @brief Gets the descriptor buffer information for a specific index.
         * @param index : The index of the instance in the buffer.
         * @return Descriptor buffer information.
        */
        VkDescriptorBufferInfo descriptorInfoForIndex(int index);

        /**
         * @brief Invalidates the mapped memory range for a specific index.
         * @param index : The index of the instance in the buffer.
         * @return Result of the invalidate operation.
        */
        VkResult invalidateIndex(int index);

        /**
         * @brief Gets the Vulkan buffer handle.
         * @return Vulkan buffer handle.
        */
        VkBuffer getBuffer() const { return buffer; }

        /**
         * @brief Gets the pointer to the mapped memory.
         * @return Pointer to the mapped memory.
        */
        void* getMappedMemory() const { return mapped; }

        /**
         * @brief Gets the number of instances in the buffer.
         * @return Number of instances.
        */
        uint32_t getInstanceCount() const { return instanceCount; }

        /**
         * @brief Gets the size of each instance in the buffer.
         * @return Size of each instance.
        */
        VkDeviceSize getInstanceSize() const { return instanceSize; }

        /**
         * @brief Gets the alignment size of the buffer.
         * @return Alignment size.
        */
        VkDeviceSize getAlignmentSize() const { return instanceSize; }

        /**
         * @brief Gets the Vulkan buffer usage flags.
         * @return Vulkan buffer usage flags.
        */
        VkBufferUsageFlags getUsageFlags() const { return usageFlags; }

        /**
         * @brief Gets the Vulkan memory property flags.
         * @return Vulkan memory property flags.
        */
        VkMemoryPropertyFlags getMemoryPropertyFlags() const { return memoryPropertyFlags; }

        /**
         * @brief Gets the total size of the buffer.
         * @return Total size of the buffer.
        */
        VkDeviceSize getBufferSize() const { return bufferSize; }


    private:
        /**
         * @brief Gets the alignment size based on the instance size and minimum offset alignment.
         * @param instanceSize : The size of each instance in the buffer.
         * @param minOffsetAlignment : Minimum alignment requirement for offsets.
         * @return Alignment size.
        */
        static VkDeviceSize getAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment);



        // ----------------- Variable -----------------
        LveDevice& lveDevice; /** @brief Vulkan logical device. */
        void* mapped = nullptr; /** @brief Pointer to the mapped memory. */
        VkBuffer buffer = VK_NULL_HANDLE; /** @brief Vulkan buffer handle. */
        VkDeviceMemory memory = VK_NULL_HANDLE; /** @brief Vulkan device memory handle. */

        VkDeviceSize bufferSize; /** @brief Total size of the buffer. */
        uint32_t instanceCount; /** @brief Number of instances in the buffer. */
        VkDeviceSize instanceSize; /** @brief Size of each instance in the buffer. */
        VkDeviceSize alignmentSize; /** @brief Alignment size of the buffer. */
        VkBufferUsageFlags usageFlags; /** @brief Vulkan buffer usage flags. */
        VkMemoryPropertyFlags memoryPropertyFlags; /** @brief Vulkan memory property flags. */
    };

}  // namespace lve