#pragma once

#include "lve_camera.hpp"
#include "lve_device.hpp"
#include "lve_pipeline.hpp"
#include "lve_game_object.hpp"
#include "lve_frame_info.hpp"

//std
#include <memory>
#include <vector>

namespace lve {
    /**
     * @brief Represents a simple rendering system using Vulkan.
    */
    class SimpleRenderSystem {
    public:
        /**
         * @brief Constructs a SimpleRenderSystem.
         * @param device : The LveDevice reference.
         * @param renderPass : The Vulkan render pass.
         * @param globalSetLayout : The Vulkan descriptor set layout.
        */
        SimpleRenderSystem(LveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
        
        /**
         * @brief Destructor to release associated resources.
        */
        ~SimpleRenderSystem();

        SimpleRenderSystem(const SimpleRenderSystem&) = delete;
        SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

        /**
         * @brief Renders game objects using the provided frame information.
         * @param frameInfo : The frame information.
        */
        void renderGameObjects(FrameInfo& frameInfo);


    private:
        /**
         * @brief Gets the current time in seconds.
         * @return The current time.
        */
        double getCurrentTime();

        /**
         * @brief Creates the Vulkan pipeline layout.
         * @param globalSetLayout : The Vulkan descriptor set layout.
        */
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        /**
         * @brief Creates the Vulkan pipeline for rendering.
         * @param renderPass : The Vulkan render pass.
        */
        void createPipeline(VkRenderPass renderPass);



        // ----------------- Variable -----------------
        LveDevice& lveDevice; /** @brief Reference to the LveDevice. */
        std::unique_ptr<LvePipeline> lvePipeline; /** @brief Unique pointer to LvePipeline. */
        VkPipelineLayout pipelineLayout; /** @brief Vulkan pipeline layout. */
    };
}