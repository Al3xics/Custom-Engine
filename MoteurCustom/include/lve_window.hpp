#pragma once

#include <vulkan/vulkan.h>
#define GLFW_INLCUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace lve {
    /**
     * @brief Represents a GLFW window for Vulkan rendering.
    */
    class LveWindow {
    public:
        /**
         * @brief Constructs an LveWindow with the specified width, height, and name.
         * @param w : The width of the window.
         * @param h : The height of the window.
         * @param name : The name of the window.
        */
        LveWindow(int w, int h, std::string name);

        /**
         * @brief Destructor for LveWindow.
        */
        ~LveWindow();

        LveWindow(const LveWindow&) = delete;
        LveWindow& operator=(const LveWindow&) = delete;

        /**
         * @brief Checks if the window should close.
         * @return True if the window should close, false otherwise.
        */
        bool shouldClose() { return glfwWindowShouldClose(window); }

        /**
         * @brief Gets the extent of the window.
         * @return VkExtent2D structure representing the width and height of the window.
        */
        VkExtent2D getExtent() { return{ static_cast<uint32_t> (width), static_cast<uint32_t> (height) }; }
        
        /**
         * @brief Checks if the window was resized.
         * @return True if the window was resized, false otherwise.
        */
        bool wasWindowResized() { return frambufferResized; }

        /**
         * @brief Resets the window resize flag.
        */
        void resetWindowResizedFlag() { frambufferResized = false; }

        /**
         * @brief Gets the GLFW window pointer.
         * @return Pointer to the GLFWwindow object.
        */
        GLFWwindow* getGLFWwindow() const { return window; }

        /**
         * @brief Creates a Vulkan window surface.
         * @param instance : The Vulkan instance.
         * @param surface : Pointer to the VkSurfaceKHR variable to store the created surface.
        */
        void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);


    private:
        /**
         * @brief Callback function for framebuffer resize events.
         * @param window : Pointer to the GLFWwindow.
         * @param width : New width of the framebuffer.
         * @param height : New height of the framebuffer.
        */
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        /**
         * @brief Initializes the GLFW window with appropriate parameters.
        */
        void initWindow();

        

        // ----------------- Variable -----------------
        int width;/** @brief Width of the window. */
        int height;/** @brief Height of the window. */
        bool frambufferResized = false;/** @brief Flag indicating whether the window was resized. */

        std::string windowName;/** @brief Name of the window. */
        GLFWwindow* window;/** @brief Pointer to the GLFW window. */
    };
} //name space lve