#pragma once

#include <functional>

namespace lve {
    /**
     * @brief Combines hash values of multiple variables into a single hash value.
     * This function uses the hash_combine algorithm to combine hash values of multiple variables.
     * @tparam T : The type of the first variable.
     * @tparam ...Rest : The types of the remaining variables.
     * @param seed : The initial hash value or the current accumulated hash value.
     * @param v : The first variable to be hashed.
     * @param ...rest : The remaining variables to be hashed.
    */
    template <typename T, typename... Rest>
    void hashCombine(std::size_t& seed, const T& v, const Rest&... rest) {
        seed ^= std::hash<T>{}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
        (hashCombine(seed, rest), ...);
    };

}  // namespace lve
