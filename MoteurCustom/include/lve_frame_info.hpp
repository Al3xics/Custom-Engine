#pragma once

#include "lve_camera.hpp"
#include "lve_game_object.hpp"

// lib
#include <vulkan/vulkan.h>

namespace lve {

#define MAX_LIGHTS 10

    /**
     * @brief Structure representing a point light source in 3D space.
    */
    struct PointLight {
        glm::vec4 position{}; /** @brief Position of the point light (ignore w component). */
        glm::vec4 color{}; /** @brief Color of the point light (w component is intensity). */
    };

    /**
     * @brief Structure representing global uniform buffer object (UBO) for shaders.
    */
    struct GlobalUbo {
        glm::mat4 projection{ 1.f }; /** @brief Projection matrix. */
        glm::mat4 view{ 1.f }; /** @brief View matrix. */
        glm::mat4 inverseView{ 1.f }; /** @brief Inverse view matrix. */
        glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f }; /** @brief Ambient light color (w component is intensity). */
        PointLight pointLights[MAX_LIGHTS]; /** @brief Array of point lights. */
        int numLights; /** @brief Number of active point lights. */
    };
    
    /**
     * @brief Structure representing information for a single frame in the rendering loop.
    */
    struct FrameInfo {
        int frameIndex; /** @brief Index of the current frame. */
        float frameTime; /** @brief Time elapsed since the last frame. */
        VkCommandBuffer commandBuffer; /** @brief Vulkan command buffer for rendering commands. */
        LveCamera& camera; /** @brief Reference to the camera used for rendering. */
        VkDescriptorSet globalDescriptorSet; /** @brief Vulkan descriptor set for global UBO binding. */
        LveGameObject::Map& gameObjects; /** @brief Reference to the map of game objects in the scene. */
    };
}  // namespace lve