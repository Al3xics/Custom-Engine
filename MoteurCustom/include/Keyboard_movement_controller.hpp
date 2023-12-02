#pragma once

#include "lve_game_object.hpp"
#include "lve_window.hpp"

namespace lve {
    /**
     * @brief Handles keyboard-based movement controls for a game object in a 3D environment.
    */
    class KeyboardMovementController {
    public:
        /**
         * @brief Defines key mappings for movement and rotation controls.
        */
        struct KeyMappings {
            int moveLeft = GLFW_KEY_A; /** @brief Key to move left. */
            int moveRight = GLFW_KEY_D; /** @brief Key to move right. */
            int moveForward = GLFW_KEY_W; /** @brief Key to move forward. */
            int moveBackward = GLFW_KEY_S; /** @brief Key to move backward. */
            int moveUp = GLFW_KEY_E; /** @brief Key to move upward. */
            int moveDown = GLFW_KEY_Q; /** @brief Key to move downward. */
            int lookLeft = GLFW_KEY_LEFT; /** @brief Key to look left. */
            int lookRight = GLFW_KEY_RIGHT; /** @brief Key to look right. */
            int lookUp = GLFW_KEY_UP; /** @brief Key to look up. */
            int lookDown = GLFW_KEY_DOWN; /** @brief Key to look down. */
        };

        /**
         * @brief Moves the game object in the XZ plane based on keyboard input.
         * @param window : The GLFW window.
         * @param dt : The time delta for smooth movement.
         * @param gameObject : The game object to be moved.
        */
        void  moveInPanelXZ(GLFWwindow* window, float dt, LveGameObject& gameObject);



        // ----------------- Variable -----------------
        KeyMappings keys{}; /** @brief Key mappings for movement and rotation controls. */
        float moveSpeed{ 3.0f }; /** @brief Movement speed. */
        float lookSpeed{ 1.5f }; /** @brief Rotation speed. */
    };
}