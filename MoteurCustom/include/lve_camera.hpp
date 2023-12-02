#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "glm/glm.hpp"

namespace lve {
    /**
     * @brief Represents a camera in a 3D scene.
    */
    class LveCamera {
    public:
        /**
         * @brief Sets the orthographic projection for the camera.
         * @param left : The left coordinate of the projection volume.
         * @param right : The right coordinate of the projection volume.
         * @param top : The top coordinate of the projection volume.
         * @param bottom : The bottom coordinate of the projection volume.
         * @param near : The near clipping plane.
         * @param far : The far clipping plane.
        */
        void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);
        
        /**
         * @brief Sets the perspective projection for the camera.
         * @param fovy : The field of view angle in the y-direction.
         * @param aspect : The aspect ratio of the viewport.
         * @param near : The near clipping plane.
         * @param far : The far clipping plane.
        */
        void setPerspectiveProjection(float fovy, float aspect, float near, float far);

        /**
         * @brief Sets the camera view direction.
         * @param position : The position of the camera.
         * @param direction : The direction the camera is facing.
         * @param up : The up vector of the camera.
        */
        void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{ 0.f,-1.f,0.f });
        
        /**
         * @brief Sets the camera view to look at a specific target.
         * @param position : The position of the camera.
         * @param target : The target position to look at.
         * @param up : The up vector of the camera.
        */
        void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{ 0.f,-1.f,0.f });
        
        /**
         * @brief Sets the camera view using yaw, pitch, and roll rotations.
         * @param position : The position of the camera.
         * @param rotation : The rotation angles in yaw, pitch, and roll order.
        */
        void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

        /**
         * @brief Gets the projection matrix of the camera.
         * @return The projection matrix.
        */
        glm::mat4 getProjection() const { return projectionMatrix; }

        /**
         * @brief Gets the view matrix of the camera.
         * @return The view matrix.
        */
        glm::mat4 getView() const { return viewMatrix; }

        /**
         * @brief Gets the inverse view matrix of the camera.
         * @return The inverse view matrix.
        */
        glm::mat4 getInverseView() const { return inverseViewMatrix; }

        /**
         * @brief Gets the position of the camera.
         * @return The position vector.
        */
        glm::vec3 getPosition() const { return glm::vec3(inverseViewMatrix[3]); }


    private:
        // ----------------- Variable -----------------
        glm::mat4 projectionMatrix{ 1.f }; /** @brief The projection matrix of the camera. */
        glm::mat4 viewMatrix{ 1.f }; /** @brief The view matrix of the camera. */
        glm::mat4 inverseViewMatrix{ 1.f }; /** @brief The inverse view matrix of the camera. */
    };
}