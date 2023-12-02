#pragma once

#include "lve_window.hpp"
#include "lve_swap_chain.hpp"
#include "lve_renderer.hpp"

namespace lve {
    /**
     * @brief Class representing an ImGui interface for Vulkan rendering.
    */
    class LveImgui {
    public:
        /**
         * @brief Constructs an LveImgui object.
         * @param window : Reference to the LveWindow object.
         * @param device : Reference to the LveDevice object.
         * @param renderer : Reference to the LveRenderer object.
        */
        LveImgui(LveWindow& window, LveDevice& device, LveRenderer& renderer);

        /**
         * @brief Destroys the LveImgui object.
        */
        ~LveImgui();

        LveImgui(const LveImgui&) = delete;
        LveImgui& operator=(const LveImgui&) = delete;

        /**
         * @brief Renders the ImGui interface.
         * @param commandBuffer : The Vulkan command buffer.
        */
        void renderImGui(VkCommandBuffer commandBuffer);

        /**
         * @brief Gets the scale slider value from the UI.
         * @param xyz : The axis (0 for X, 1 for Y, 2 for Z).
         * @return The scale value.
        */
        float getScaleSliderValue(int xyz);

        /**
         * @brief Gets the rotation slider value from the UI.
         * @param xyz : The axis (0 for X, 1 for Y, 2 for Z).
         * @return The rotation value.
        */
        float getRotationSliderValue(int xyz);

        /**
         * @brief Gets the position slider value from the UI.
         * @param xyz : The axis (0 for X, 1 for Y, 2 for Z).
         * @return The position value.
        */
        float getPositionSliderValue(int xyz);


    private:

        /**
         * @brief Initializes the ImGui context, style, and backends for GLFW and Vulkan.
         * Creates the ImGui fonts texture.
        */
        void initImGui();
        /**
         * @brief Initializes an ImGui inspector window.
         * Displays the ImGui demo window if the show_demo_window flag is enabled.
         * Displays a "Create Cube" button that triggers cube creation (cubecre is set to true).
         * If cubecre is true, displays ImGui controls to set cube properties (myCube).
         * Displays text with average frame time and application FPS.
        */
        void initInspector();



        // ----------------- Variable -----------------
        LveWindow& lveWindow; /** @brief Reference to the LveWindow object. */
        LveDevice& lveDevice; /** @brief Reference to the LveDevice object. */
        LveRenderer& lveRenderer; /** @brief Reference to the LveRenderer object. */
        VkDescriptorPool imguiPool; /** @brief Vulkan descriptor pool for ImGui. */
    };
}