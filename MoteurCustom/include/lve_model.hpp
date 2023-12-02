#pragma once
#include "lve_device.hpp"
#include "lve_buffer.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "glm/glm.hpp"

//std
#include <memory>
#include <vector>

namespace lve {
    /**
     * @brief Represents a 3D model in Vulkan.
    */
    class LveModel {
    public:
        /**
         * @brief Represents a vertex in the model.
        */
        struct Vertex {
            glm::vec3 position; /** @brief Vertex position. */
            glm::vec3 color; /** @brief Vertex color. */
            glm::vec3 normal; /** @brief Vertex normal. */
            glm::vec2 uv; /** @brief Vertex UV coordinates. */

            /**
             * @brief Gets the binding descriptions for Vulkan vertex input.
             * @return A vector of VkVertexInputBindingDescription.
            */
            static std::vector<VkVertexInputBindingDescription>getBindingDescriptions();

            /**
             * @brief Gets the attribute descriptions for Vulkan vertex input.
             * @return A vector of VkVertexInputAttributeDescription.
            */
            static std::vector<VkVertexInputAttributeDescription>getAttributeDescriptions();

            /**
             * @brief Checks if two vertices are equal.
             * @param other : The other vertex to compare with.
             * @return True if the vertices are equal, false otherwise.
            */
            bool operator == (const Vertex& other)const {
                return position == other.position && color == other.color && normal == other.normal && uv == other.uv;
            }
        };

        /**
         * @brief Represents a builder for creating a model.
        */
        struct Builder {
            std::vector<Vertex> vertices{}; /** @brief Vector of vertices. */
            std::vector<uint32_t> indices{}; /** @brief Vector of indices. */

            /**
             * @brief Loads a model from a file.
             * @param filepath : The path to the model file.
            */
            void loadModel(const std::string& filepath);
        };

        /**
         * @brief Constructs an LveModel object.
         * @param device : The Vulkan device.
         * @param builder : The model builder.
        */
        LveModel(LveDevice& device, const LveModel::Builder& builder);

        /**
         * @brief Destroys the LveModel object.
        */
        ~LveModel();

        LveModel(const LveModel&) = delete;
        LveModel& operator=(const LveModel&) = delete;

        /**
         * @brief Creates a model from a file.
         * @param device : The Vulkan device.
         * @param filePath : The path to the model file.
         * @return A unique pointer to the created LveModel.
        */
        static std::unique_ptr <LveModel> createModelFromFile(LveDevice& device, const std::string& filePath);
        
        /**
         * @brief Binds the model to a Vulkan command buffer.
         * @param commandBuffer : The Vulkan command buffer.
        */
        void bind(VkCommandBuffer commandBuffer);

        /**
         * @brief Draws the model using a Vulkan command buffer.
         * @param commandBuffer : The Vulkan command buffer.
        */
        void draw(VkCommandBuffer commandBuffer);


    private:
        /**
         * @brief Creates the vertex buffers for the model.
         * @param vertices : The vector of vertices.
        */
        void createVertexBuffers(const std::vector<Vertex>& vertices);

        /**
         * @brief Creates the index buffers for the model.
         * @param indices : The vector of indices.
        */
        void createIndexBuffers(const std::vector<uint32_t>& indices);



        // ----------------- Variable -----------------
        LveDevice& lveDevice; /** @brief Vulkan device. */
        std::unique_ptr<LveBuffer> vertexBuffer; /** @brief Vertex buffer. */
        uint32_t vertexCount; /** @brief Number of vertices. */
        bool hasIndexBuffer = false; /** @brief Flag indicating the presence of an index buffer. */
        std::unique_ptr<LveBuffer> indexBuffer; /** @brief Index buffer. */
        uint32_t indexCount; /** @brief Number of indices. */
    };
}