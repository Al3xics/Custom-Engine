#pragma once

#include "lve_device.hpp"
#include "lve_renderer.hpp"
#include "lve_window.hpp"
#include "lve_game_object.hpp"
#include "lve_descriptors.hpp"
#include "lve_imgui.hpp"

//std
#include <memory>
#include <vector>

namespace lve {
    /**
     * @brief Main class representing the application.
    */
    class FirstApp {
    public:
        static constexpr int WIDTH = 1280; /** @brief Width of the application window. */
        static constexpr int HEIGHT = 720; /** @brief Height of the application window. */

        /**
         * @brief Default constructor for the FirstApp class.
        */
        FirstApp();

        /**
         * @brief Destructor for the FirstApp class.
        */
        ~FirstApp();

        FirstApp(const FirstApp&) = delete;
        FirstApp& operator=(const FirstApp&) = delete;

        /**
         * @brief Main function to run the application.
        */
        void run();


    private:
        /**
         * @brief Helper function to get the current time.
         * @return Current time in seconds.
        */
        double getCurrentTime();

        /**
         * @brief Load game objects for the application.
        */
        void loadGameObjects();

        /**
         * @brief Load collision cubes for the application.
        */
        void loadCubesCollision();



        // ----------------- Variable -----------------
        LveWindow lveWindow{ WIDTH, HEIGHT, "GG ENGINE" }; /** @brief Main application window. */
        LveDevice lveDevice{ lveWindow }; /** @brief Vulkan device for rendering. */
        LveRenderer lveRenderer{ lveWindow,lveDevice }; /** @brief Renderer for rendering graphics. */
        LveImgui lveImgui{ lveWindow, lveDevice, lveRenderer }; /** @brief ImGui integration for UI. */

        // note: order of declarations matters
        std::unique_ptr<LveDescriptorPool> globalPool{}; /** @brief Descriptor pool for global settings. */
        LveGameObject::Map gameObjects; /** @brief Map of game objects in the application. */
    };
}