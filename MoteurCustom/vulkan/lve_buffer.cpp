#include "lve_buffer.hpp"

 // std
#include <cassert>
#include <cstring>

namespace lve {
    VkDeviceSize LveBuffer::getAlignment(VkDeviceSize instanceSize, VkDeviceSize minOffsetAlignment) {
        if (minOffsetAlignment > 0) {
            return (instanceSize + minOffsetAlignment - 1) & ~(minOffsetAlignment - 1);
        }
        return instanceSize;
    }

    LveBuffer::LveBuffer(LveDevice& device, VkDeviceSize instanceSize, uint32_t instanceCount, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize minOffsetAlignment) : lveDevice{ device }, instanceSize{ instanceSize }, instanceCount{ instanceCount }, usageFlags{ usageFlags }, memoryPropertyFlags{ memoryPropertyFlags } {
        alignmentSize = getAlignment(instanceSize, minOffsetAlignment);
        bufferSize = alignmentSize * instanceCount;
        device.createBuffer(bufferSize, usageFlags, memoryPropertyFlags, buffer, memory);
    }

    LveBuffer::~LveBuffer() {
        unmap();
        vkDestroyBuffer(lveDevice.getDevice(), buffer, nullptr);
        vkFreeMemory(lveDevice.getDevice(), memory, nullptr);
    }

    VkResult LveBuffer::map(VkDeviceSize size, VkDeviceSize offset) {
        assert(buffer && memory && "Called map on buffer before create");
        return vkMapMemory(lveDevice.getDevice(), memory, offset, size, 0, &mapped);
    }

    void LveBuffer::unmap() {
        if (mapped) {
            vkUnmapMemory(lveDevice.getDevice(), memory);
            mapped = nullptr;
        }
    }

    void LveBuffer::writeToBuffer(void* data, VkDeviceSize size, VkDeviceSize offset) {
        assert(mapped && "Cannot copy to unmapped buffer");

        if (size == VK_WHOLE_SIZE) {
            memcpy(mapped, data, bufferSize);
        } else {
            char* memOffset = (char*)mapped;
            memOffset += offset;
            memcpy(memOffset, data, size);
        }
    }

    VkResult LveBuffer::flush(VkDeviceSize size, VkDeviceSize offset) {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = memory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkFlushMappedMemoryRanges(lveDevice.getDevice(), 1, &mappedRange);
    }

    VkResult LveBuffer::invalidate(VkDeviceSize size, VkDeviceSize offset) {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = memory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkInvalidateMappedMemoryRanges(lveDevice.getDevice(), 1, &mappedRange);
    }

    VkDescriptorBufferInfo LveBuffer::descriptorInfo(VkDeviceSize size, VkDeviceSize offset) {
        return VkDescriptorBufferInfo{ buffer, offset, size, };
    }

    void LveBuffer::writeToIndex(void* data, int index) {
        writeToBuffer(data, instanceSize, index * alignmentSize);
    }

    VkResult LveBuffer::flushIndex(int index) {
        return flush(alignmentSize, index * alignmentSize);
    }

    VkDescriptorBufferInfo LveBuffer::descriptorInfoForIndex(int index) {
        return descriptorInfo(alignmentSize, index * alignmentSize);
    }

    VkResult LveBuffer::invalidateIndex(int index) {
        return invalidate(alignmentSize, index * alignmentSize);
    }

}  // namespace lve
