#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>

//#include "lve_model.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "AABB.hpp"
#include "Sphere.hpp"

namespace lve {
    /**
     * @brief The Collision class provides methods for various collision detection operations.
    */
    class Colision {
    public:
        /**
         * @brief Checks if a given point is inside an axis-aligned bounding box (AABB).
         * @param point : The point to be checked.
         * @param box : The AABB to check against.
         * @return True if the point is inside the AABB, false otherwise.
        */
        bool isPointInsideAABB(glm::vec3 point, AABB box) { //AABB = axis-aligned bounding box
            return (
                point.x >= box.minX &&
                point.x <= box.maxX &&
                point.y >= box.minY &&
                point.y <= box.maxY &&
                point.z >= box.minZ &&
                point.z <= box.maxZ
                );
        }

        /**
         * @brief Checks if a given point is inside a sphere.
         * @param point : The point to be checked.
         * @param sphere : The sphere to check against.
         * @return True if the point is inside the sphere, false otherwise.
        */
        bool isPointInsideSphere(glm::vec3 point, Sphere sphere) {
            float distance = sqrt(
                (point.x - sphere.x) * (point.x - sphere.x) +
                (point.y - sphere.y) * (point.y - sphere.y) +
                (point.z - sphere.z) * (point.z - sphere.z)
            );
            return distance < sphere.radius;
        }

        /**
         * @brief Checks if two AABBs intersect.
         * @param boxA : The first AABB.
         * @param boxB : The second AABB.
         * @return True if the AABBs intersect, false otherwise.

        */
        bool isIntersectAABB2(AABB boxA, AABB boxB) {
            return (
                boxA.minX <= boxB.maxX &&
                boxA.maxX >= boxB.minX &&
                boxA.minY <= boxB.maxY &&
                boxA.maxY >= boxB.minY &&
                boxA.minZ <= boxB.maxZ &&
                boxA.maxZ >= boxB.minZ
                );
        }

        /**
         * @brief Checks if two spheres intersect.
         * @param sphereA : The first sphere.
         * @param sphereB : The second sphere.
         * @return True if the spheres intersect, false otherwise.
        */
        bool isIntersectSphere2(Sphere sphereA, Sphere sphereB) {
            float distance = sqrt(
                (sphereA.x - sphereB.x) * (sphereA.x - sphereB.x) +
                (sphereA.y - sphereB.y) * (sphereA.y - sphereB.y) +
                (sphereA.z - sphereB.z) * (sphereA.z - sphereB.z)
            );
            return distance < sphereA.radius + sphereB.radius;
        }

        /**
         * @brief Checks if a sphere intersects with an AABB.
         * @param sphere : The sphere to check.
         * @param box : The AABB to check against.
         * @return True if the sphere intersects with the AABB, false otherwise.
        */
        bool isIntersectSphereAABB(Sphere sphere, AABB box) {
            float x = this->max(box.minX, this->min(sphere.x, box.maxX));
            float y = this->max(box.minY, this->min(sphere.y, box.maxY));
            float z = this->max(box.minZ, this->min(sphere.z, box.maxZ));

            float distance = sqrt(
                (x - sphere.x) * (x - sphere.x) +
                (y - sphere.y) * (y - sphere.y) +
                (z - sphere.z) * (z - sphere.z)
            );

            return distance < sphere.radius;
        }


    private:
        /**
         * @brief Returns the smaller of two floating-point values.
         * @param a : The first value.
         * @param b : The second value.
         * @return The smaller of the two values.
        */
        float min(float a, float b) {
            float res = a;

            if (a > b) {
                res = b;
            }

            return res;
        }
        /**
         * @brief Returns the larger of two floating-point values.
         * @param a : The first value.
         * @param b :  The second value.
         * @return The larger of the two values.
        */
        float max(float a, float b) {
            float res = b;

            if (a >= b) {
                res = a;
            }

            return res;
        }
    };
}