#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace lve {
    /**
     * @brief The Sphere class represents a three-dimensional sphere in space.
    */
    class Sphere {
    public:
        float x; /** @brief X-coordinate of the sphere's center. */
        float y; /** @brief Y-coordinate of the sphere's center. */
        float z; /** @brief Z-coordinate of the sphere's center. */
        float radius; /** @brief Radius of the sphere. */

        /**
         * @brief Default constructor initializes a sphere with center at the origin and radius 1.0.
        */
        Sphere() {
            this->x = 0.0;
            this->y = 0.0;
            this->z = 0.0;
            this->radius = 1.0;
        }

        /**
         * @brief Constructor initializes a sphere with a specified center point and radius.
         * @param point : The center point of the sphere.
         * @param radius : The radius of the sphere.
        */
        Sphere(glm::vec3 point, float radius) {
            this->x = point.x;
            this->y = point.y;
            this->z = point.z;
            this->radius = radius;
        }
        /**
         * @brief Constructor initializes a sphere with specified coordinates and radius.
         * @param x : X-coordinate of the sphere's center.
         * @param y : Y-coordinate of the sphere's center.
         * @param z : Z-coordinate of the sphere's center.
         * @param radius : The radius of the sphere.
        */
        Sphere(float x, float y, float z, float radius) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->radius = radius;
        }

        /**
         * @brief Copy constructor creates a new sphere with the same attributes as the provided sphere.
         * @param s : The sphere to be copied.
        */
        Sphere(const Sphere& s) {
            this->x = s.x;
            this->y = s.y;
            this->z = s.z;
            this->radius = s.radius;
        }
    };
}