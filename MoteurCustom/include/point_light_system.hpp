#pragma once

#include "lve_camera.hpp"
#include "lve_device.hpp"
#include "lve_frame_info.hpp"
#include "lve_game_object.hpp"
#include "lve_pipeline.hpp"


//std
#include <memory>
#include <vector>


namespace lve {
    /**
     * @brief Class representing a Point Light System in a Vulkan application.
     * This class manages the rendering and updating of point lights in the application.
    */
    class PointLightSystem {
    public:
        /**
         * @brief Constructor initializing the system with a logical device, Vulkan render pass, and global descriptor layout.
         * @param device : The logical device.
         * @param renderPass : The Vulkan render pass.
         * @param globalSetLayout : The layout of global descriptors.
        */
        PointLightSystem(LveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);

        /**
         * @brief Destructor.
        */
        ~PointLightSystem();

        PointLightSystem(const PointLightSystem&) = delete;
        PointLightSystem& operator=(const PointLightSystem&) = delete;

        /**
         * @brief Update function to be called per frame for updating point light information.
         * @param frameInfo : Information about the current frame.
         * @param ubo : The global uniform buffer object.
        */
        void update(FrameInfo& frameInfo, GlobalUbo& ubo);

        /**
         * @brief Render function to render point lights.
         * @param frameInfo : Information about the current frame.
        */
        void render(FrameInfo& frameInfo);


    private:
        /**
         * @brief Get the current time.
         * @return The current time.
        */
        double getCurrentTime();

        /**
         * @brief Create the pipeline layout for the point light system.
         * @param globalSetLayout : The layout of global descriptors.
        */
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        /**
         * @brief Create the pipeline for rendering point lights.
         * @param renderPass : The Vulkan render pass.
        */
        void createPipeline(VkRenderPass renderPass);



        // ----------------- Variable -----------------
        LveDevice& lveDevice; /** @brief Reference to the logical device. */
        std::unique_ptr<LvePipeline> lvePipeline; /** @brief Unique pointer to the pipeline. */
        VkPipelineLayout pipelineLayout; /** @brief Vulkan pipeline layout. */
    };
}