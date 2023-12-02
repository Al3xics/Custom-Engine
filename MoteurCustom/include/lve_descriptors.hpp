#pragma once

#include "lve_device.hpp"

// std
#include <memory>
#include <unordered_map>
#include <vector>

namespace lve {
    /**
     * @brief Represents a descriptor set layout in Vulkan.
    */
    class LveDescriptorSetLayout {
    public:
        /**
         * @brief Builder class for constructing LveDescriptorSetLayout instances.
        */
        class Builder {
        public:
            /**
             * @brief Constructs a LveDescriptorSetLayout::Builder object.
             * @param lveDevice : The logical Vulkan device.
            */
            Builder(LveDevice& lveDevice) : lveDevice{ lveDevice } {}

            /**
             * @brief Adds a binding to the descriptor set layout.
             * @param binding : The binding index.
             * @param descriptorType : The type of descriptor.
             * @param stageFlags : The shader stage flags.
             * @param count : The number of descriptors in the binding.
             * @return Reference to the Builder for method chaining.
            */
            Builder& addBinding(uint32_t binding, VkDescriptorType descriptorType, VkShaderStageFlags stageFlags, uint32_t count = 1);
            
            /**
             * @brief Builds a LveDescriptorSetLayout instance.
             * @return Unique pointer to the constructed LveDescriptorSetLayout.
            */
            std::unique_ptr<LveDescriptorSetLayout> build() const;

        private:
            LveDevice& lveDevice; /** @brief The logical Vulkan device. */
            std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{}; /** @brief Map of binding indices to descriptor set layout bindings. */
        };

        /**
         * @brief Constructs a LveDescriptorSetLayout.
         * @param lveDevice : The logical Vulkan device.
         * @param bindings : Map of binding indices to descriptor set layout bindings.
        */
        LveDescriptorSetLayout(LveDevice& lveDevice, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
        
        /**
         * @brief Destructor for LveDescriptorSetLayout.
        */
        ~LveDescriptorSetLayout();

        LveDescriptorSetLayout(const LveDescriptorSetLayout&) = delete;
        LveDescriptorSetLayout& operator=(const LveDescriptorSetLayout&) = delete;

        /**
         * @brief Gets the Vulkan descriptor set layout handle.
         * @return The Vulkan descriptor set layout handle.
        */
        VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }


    private:
        LveDevice& lveDevice; /** @brief The logical Vulkan device. */
        VkDescriptorSetLayout descriptorSetLayout; /** @brief The Vulkan descriptor set layout handle. */
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings; /** @brief Map of binding indices to descriptor set layout bindings. */

        friend class LveDescriptorWriter; /** @brief Friend class for access to private members. */
    };

    /**
     * @brief Represents a descriptor pool in Vulkan.
    */
    class LveDescriptorPool {
    public:
        /**
         * @brief Builder class for constructing LveDescriptorPool instances.
        */
        class Builder {
        public:
            /**
             * @brief Constructs a LveDescriptorPool::Builder object.
             * @param lveDevice : The logical Vulkan device.
            */
            Builder(LveDevice& lveDevice) : lveDevice{ lveDevice } {}

            /**
             * @brief Adds a pool size for a specific descriptor type.
             * @param descriptorType : The type of descriptor.
             * @param count : The number of descriptors in the pool.
             * @return Reference to the Builder for method chaining.
            */
            Builder& addPoolSize(VkDescriptorType descriptorType, uint32_t count);

            /**
             * @brief Sets the flags for the descriptor pool.
             * @param flags : The descriptor pool create flags.
             * @return Reference to the Builder for method chaining.
            */
            Builder& setPoolFlags(VkDescriptorPoolCreateFlags flags);

            /**
             * @brief Sets the maximum number of descriptor sets that can be allocated from the pool.
             * @param count : The maximum number of descriptor sets.
             * @return Reference to the Builder for method chaining.
            */
            Builder& setMaxSets(uint32_t count);

            /**
             * @brief Builds a LveDescriptorPool instance.
             * @return Unique pointer to the constructed LveDescriptorPool.
            */
            std::unique_ptr<LveDescriptorPool> build() const;

        private:
            LveDevice& lveDevice; /** @brief The logical Vulkan device. */
            std::vector<VkDescriptorPoolSize> poolSizes{}; /** @brief Vector of descriptor pool sizes for different descriptor types. */
            uint32_t maxSets = 1000; /** @brief The maximum number of descriptor sets. */
            VkDescriptorPoolCreateFlags poolFlags = 0; /** @brief The descriptor pool create flags. */
        };

        /**
         * @brief Constructs a LveDescriptorPool.
         * @param lveDevice : The logical Vulkan device.
         * @param maxSets : The maximum number of descriptor sets.
         * @param poolFlags : The descriptor pool create flags.
         * @param poolSizes : Vector of descriptor pool sizes for different descriptor types.
        */
        LveDescriptorPool(LveDevice& lveDevice, uint32_t maxSets, VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize>& poolSizes);
        
        /**
         * @brief Destructor for LveDescriptorPool.
        */
        ~LveDescriptorPool();

        LveDescriptorPool(const LveDescriptorPool&) = delete;
        LveDescriptorPool& operator=(const LveDescriptorPool&) = delete;

        /**
         * @brief Allocates a descriptor set from the pool.
         * @param descriptorSetLayout : The descriptor set layout to allocate from.
         * @param descriptor : Reference to the allocated descriptor set.
         * @return True if allocation is successful, false otherwise.
        */
        bool allocateDescriptor(const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet& descriptor) const;
        
        /**
         * @brief Frees a vector of descriptor sets.
         * @param descriptors : Vector of descriptor sets to free.
        */
        void freeDescriptors(std::vector<VkDescriptorSet>& descriptors) const;

        /**
         * @brief Resets the descriptor pool.
        */
        void resetPool();

        /**
         * @brief Gets the Vulkan descriptor pool handle.
         * @return The Vulkan descriptor pool handle.
        */
        VkDescriptorPool getDescriptorPool() const;


    private:
        LveDevice& lveDevice; /** @brief The logical Vulkan device. */
        VkDescriptorPool descriptorPool; /** @brief The Vulkan descriptor pool handle. */

        friend class LveDescriptorWriter; /** @brief Friend class for access to private members. */
    };

    /**
     * @brief Represents a descriptor writer in Vulkan.
    */
    class LveDescriptorWriter {
    public:
        /**
         * @brief Constructs a LveDescriptorWriter.
         * @param setLayout : The descriptor set layout to write to.
         * @param pool : The descriptor pool to allocate from.
        */
        LveDescriptorWriter(LveDescriptorSetLayout& setLayout, LveDescriptorPool& pool);

        /**
         * @brief Writes buffer information to a specified binding.
         * @param binding : The binding index.
         * @param bufferInfo : Pointer to VkDescriptorBufferInfo.
         * @return Reference to the LveDescriptorWriter for method chaining.
        */
        LveDescriptorWriter& writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo);

        /**
         * @brief Writes image information to a specified binding.
         * @param binding : The binding index.
         * @param imageInfo : Pointer to VkDescriptorImageInfo.
         * @return Reference to the LveDescriptorWriter for method chaining.
        */
        LveDescriptorWriter& writeImage(uint32_t binding, VkDescriptorImageInfo* imageInfo);

        /**
         * @brief Builds and allocates a descriptor set.
         * @param set : Reference to the allocated descriptor set.
         * @return True if allocation is successful, false otherwise.
        */
        bool build(VkDescriptorSet& set);

        /**
         * @brief Overwrites an existing descriptor set with the configured writes.
         * @param set : The descriptor set to overwrite.
        */
        void overwrite(VkDescriptorSet& set);


    private:
        LveDescriptorSetLayout& setLayout; /** @brief The descriptor set layout to write to. */
        LveDescriptorPool& pool; /** @brief The descriptor pool to allocate from. */
        std::vector<VkWriteDescriptorSet> writes; /** @brief Vector of descriptor set writes. */
    };

}  // namespace lve