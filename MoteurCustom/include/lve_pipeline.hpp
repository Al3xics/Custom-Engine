#pragma once

#include "lve_device.hpp"
#include <string>
#include <vector>
namespace lve {
    /**
     * @brief Configuration structure for Vulkan pipeline settings.
    */
    struct PipeLineConfigInfo {
        PipeLineConfigInfo(const PipeLineConfigInfo&) = delete;
        PipeLineConfigInfo& operator=(const PipeLineConfigInfo&) = delete;
        PipeLineConfigInfo() = default;

        //VkViewport viewport;
        std::vector<VkVertexInputBindingDescription> bindingDescriptions{}; /** @brief Vertex input binding descriptions. */
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions{}; /** @brief Vertex input attribute descriptions. */
        VkPipelineViewportStateCreateInfo viewportInfo; /** @brief Viewport state information. */
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo; /** @brief Input assembly state information. */
        VkPipelineRasterizationStateCreateInfo rasterizationInfo; /** @brief Rasterization state information. */
        VkPipelineMultisampleStateCreateInfo multisampleInfo; /** @brief Multisample state information. */
        VkPipelineColorBlendAttachmentState colorBlendAttachment; /** @brief Color blend attachment state. */
        VkPipelineColorBlendStateCreateInfo colorBlendInfo; /** @brief Color blend state information. */
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo; /** @brief Depth and stencil state information. */
        std::vector<VkDynamicState> dynamicStateEnables; /** @brief List of dynamic states to enable. */
        VkPipelineDynamicStateCreateInfo dynamicStateInfo; /** @brief Dynamic state information. */
        VkPipelineLayout pipelineLayout = nullptr; /** @brief Vulkan pipeline layout. */
        VkRenderPass renderPass = nullptr; /** @brief Vulkan render pass. */
        uint32_t subpass = 0; /** @brief Subpass index. */

    };

    /**
     * @brief Represents a Vulkan graphics pipeline.
    */
    class LvePipeline {
    public:
        /**
         * @brief Constructs an LvePipeline.
         * @param device : The LveDevice reference.
         * @param vertFilePath : The path to the vertex shader file.
         * @param fragFilePath : The path to the fragment shader file.
         * @param configInfo : The pipeline configuration information.
        */
        LvePipeline(LveDevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipeLineConfigInfo& configInfo);
        
        /**
         * @brief Destructor to release associated resources.
        */
        ~LvePipeline();

        LvePipeline(const LvePipeline&) = delete;
        LvePipeline& operator=(const LvePipeline&) = delete;
        LvePipeline() = default;

        /**
         * @brief Binds the graphics pipeline to the specified Vulkan command buffer.
         * @param VkCommandBuffer : The Vulkan command buffer.
        */
        void bind(VkCommandBuffer(commandBuffer));

        /**
         * @brief Initializes the given PipeLineConfigInfo structure with default values.
         * @param configInfo : The configuration structure to be initialized.
        */
        static void defaultPipeLineConfigInfo(PipeLineConfigInfo& configInfo);

        /**
         * @brief Enables alpha blending in the specified PipeLineConfigInfo structure.
         * @param configInfo : The configuration structure to enable alpha blending.
        */
        static void enableAlphaBlending(PipeLineConfigInfo& configInfo);

    private:
        /**
         * @brief Reads the content of a file and returns it as a vector of characters.
         * @param filepath : The path to the file.
         * @return The content of the file as a vector of characters.
        */
        static std::vector<char> readFile(const std::string& filepath);

        /**
         * @brief Creates the Vulkan graphics pipeline using specified shader files and configuration.
         * @param vertFilepath : The path to the vertex shader file.
         * @param fragFilepath : The path to the fragment shader file.
         * @param configInfo : The pipeline configuration information.
        */
        void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipeLineConfigInfo& configInfo);
        
        /**
         * @brief Creates a Vulkan shader module from the provided shader code.
         * @param code : The shader code.
         * @param shaderModule : Pointer to store the created shader module.
        */
        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);



        // ----------------- Variable -----------------
        LveDevice& lveDevice; /** @brief Reference to the LveDevice. */
        VkPipeline graphicsPipeline; /** @brief Vulkan graphics pipeline. */
        VkShaderModule vertShaderModule; /** @brief Vertex shader module. */
        VkShaderModule fragShaderModule; /** @brief Fragment shader module. */
    };
}