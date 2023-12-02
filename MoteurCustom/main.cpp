#include "firstapp.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

/**
 * @brief Main function to execute the application.
 * @return EXIT_SUCCESS if the application runs successfully, EXIT_FAILURE otherwise.
*/
int main() {
    // Changer "lve_swap_chain.cpp" --> "chooseSwapSurfaceFormat()" en "..._SRGB" ou "..._UNORM"
    lve::FirstApp app{};

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}