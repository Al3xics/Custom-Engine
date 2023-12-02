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
#include "Sphere.hpp"

namespace lve {
    /**
     * @brief Class representing an axis-aligned bounding box (AABB) used for collision detection.
    */
    class AABB {
    public:
        float minX; /** @brief Minimum X-coordinate of the AABB. */
        float maxX; /** @brief Maximum X-coordinate of the AABB. */
        float minY; /** @brief Minimum Y-coordinate of the AABB. */
        float maxY; /** @brief Maximum Y-coordinate of the AABB. */
        float minZ; /** @brief Minimum Z-coordinate of the AABB. */
        float maxZ; /** @brief Maximum Z-coordinate of the AABB. */

        /**
         * @brief Default constructor initializes the AABB with zeroed coordinates.
        */
        AABB() {
            this->minX = 0.0;
            this->maxX = 0.0;

            this->minY = 0.0;
            this->maxY = 0.0;

            this->minZ = 0.0;
            this->maxZ = 0.0;
        }

        /**
         * @brief Constructor initializes the AABB with two points in 3D space.
         * @param pointA : The first point.
         * @param pointB : The second point.
        */
        AABB(glm::vec3 pointA, glm::vec3 pointB) {
            this->minX = (pointA.x < pointB.x) ? pointA.x : pointB.x;
            this->maxX = (pointA.x > pointB.x) ? pointA.x : pointB.x;

            this->minY = (pointA.y < pointB.y) ? pointA.y : pointB.y;
            this->maxY = (pointA.y > pointB.y) ? pointA.y : pointB.y;

            this->minZ = (pointA.z < pointB.z) ? pointA.z : pointB.z;
            this->maxZ = (pointA.z > pointB.z) ? pointA.z : pointB.z;
        }

        /**
         * @brief Constructor initializes the AABB with specified coordinate values.
         * @param minX : Minimum X-coordinate.
         * @param maxX : Maximum X-coordinate.
         * @param minY : Minimum Y-coordinate.
         * @param maxY : Maximum Y-coordinate.
         * @param minZ : Minimum Z-coordinate.
         * @param maxZ : Maximum Z-coordinate.
        */
        AABB(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
            this->minX = minX;
            this->maxX = maxX;

            this->minY = minY;
            this->maxY = maxY;

            this->minZ = minZ;
            this->maxZ = maxZ;
        }

        /**
         * @brief Copy constructor creates a new AABB with the same coordinates as the provided AABB.
         * @param box : The AABB to be copied.
        */
        AABB(const AABB& box) {
            this->minX = box.minX;
            this->maxX = box.maxX;

            this->minY = box.minY;
            this->maxY = box.maxY;

            this->minZ = box.minZ;
            this->maxZ = box.maxZ;
        }

        /**
         * @brief Sets the coordinates of the AABB using two points in 3D space.
         * @param pointA : The first point.
         * @param pointB : The second point.
        */
        void setBoxPoint(glm::vec3 pointA, glm::vec3 pointB) {
            this->minX = (pointA.x < pointB.x) ? pointA.x : pointB.x;
            this->maxX = (pointA.x > pointB.x) ? pointA.x : pointB.x;

            this->minY = (pointA.y < pointB.y) ? pointA.y : pointB.y;
            this->maxY = (pointA.y > pointB.y) ? pointA.y : pointB.y;

            this->minZ = (pointA.z < pointB.z) ? pointA.z : pointB.z;
            this->maxZ = (pointA.z > pointB.z) ? pointA.z : pointB.z;
        }

        /**
         * @brief Checks if a sphere intersects with the AABB.
         * @param sphere : The sphere to check.
         * @return True if the sphere intersects with the AABB, false otherwise.
        */
        bool isIntersectSphere(Sphere sphere) {
            float x = this->max(this->minX, this->min(sphere.x, this->maxX));
            float y = this->max(this->minY, this->min(sphere.y, this->maxY));
            float z = this->max(this->minZ, this->min(sphere.z, this->maxZ));

            float distance = sqrt(
                (x - sphere.x) * (x - sphere.x) +
                (y - sphere.y) * (y - sphere.y) +
                (z - sphere.z) * (z - sphere.z)
            );

            return distance < sphere.radius;
        }

        /**
         * @brief Calculates the normal vector for collision response with a sphere.
         * @param sphere : The sphere involved in the collision.
         * @return The collision normal vector.
        */
        glm::vec3 normIntersectSphere(Sphere sphere) {
            glm::vec3 norm = { 0.f, 0.f, 0.f };

            // Calcul du point le plus proche de la sphère sur le cube
            float x = glm::clamp(sphere.x, this->minX, this->maxX);
            float y = glm::clamp(sphere.y, this->minY, this->maxY);
            float z = glm::clamp(sphere.z, this->minZ, this->maxZ);

            // Calcul de la normale basée sur le point le plus proche
            norm.x = sphere.x - x;
            norm.y = sphere.y - y;
            norm.z = sphere.z - z;

            // Normalisation de la normale
            norm = glm::normalize(norm);

            return norm;
        }

        /**
         * @brief Checks if two AABBs intersect.
         * @param box : The other AABB to check against.
         * @return True if the AABBs intersect, false otherwise.
        */
        bool isIntersectAABB(AABB box) {
            return (
                box.minX <= this->maxX &&
                box.maxX >= this->minX &&
                box.minY <= this->maxY &&
                box.maxY >= this->minY &&
                box.minZ <= this->maxZ &&
                box.maxZ >= this->minZ
                );
        }

        /**
         * @brief Determines the direction of separation for collision response between two AABBs.
         * @param box : The other AABB involved in the collision.
         * @return The collision normal vector.
        */
        glm::vec3 normIntersectAABB(AABB box) {
            glm::vec3 norm = { 1.f, 1.f, 1.f };

            if (isIntersectAABB(box)) {
                float xOverlap = std::min(this->maxX, box.maxX) - std::max(this->minX, box.minX);
                float yOverlap = std::min(this->maxY, box.maxY) - std::max(this->minY, box.minY);
                float zOverlap = std::min(this->maxZ, box.maxZ) - std::max(this->minZ, box.minZ);

                if (xOverlap < yOverlap && xOverlap < zOverlap) {
                    //Face touchée : face X
                    norm = { -1.f, 1.f, 1.f };
                } else if (yOverlap < xOverlap && yOverlap < zOverlap) {
                    //Face touchée : face Y
                    norm = { 1.f, -1.f, 1.f };
                } else {
                    //Face touchée : face Z
                    norm = { 1.f, 1.f, -1.f };
                }
            }

            return norm;
        }

        /**
         * @brief Checks if a given point is inside the AABB.
         * @param point : The point to be checked.
         * @return True if the point is inside the AABB, false otherwise.
        */
        bool isPointInside(glm::vec3 point) { //AABB = axis-aligned bounding box
            return (
                point.x >= this->minX &&
                point.x <= this->maxX &&
                point.y >= this->minY &&
                point.y <= this->maxY &&
                point.z >= this->minZ &&
                point.z <= this->maxZ
                );
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
         * @param b : The second value.
         * @return The larger of the two values.
        */
        float max(float a, float b) {
            float res = b;

            if (a >= b) {
                res = a;
            }

            return res;
        }

        /**
         * @brief Returns the coordinates of the center point of the AABB.
         * @return The center coordinates.
        */
        glm::vec3 center() {
            return { minX + ((minX - maxX) / 2), minY + ((minY - maxY) / 2), minZ + ((minZ - maxZ) / 2) };
        }
    };
}