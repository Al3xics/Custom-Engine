#pragma once

#include "lve_model.hpp"
//libs
#include "glm/gtc/matrix_transform.hpp"
#include "Colision.hpp"

//Std
#include <memory>
#include <unordered_map>

namespace lve {
    /**
     * @brief Structure representing the transformation component of a game object.
    */
    struct TransformComponent {
        glm::vec3 translation{}; /** @brief Translation vector. */
        glm::vec3 scale{ 1.f,1.f,1.f }; /** @brief Scale vector. */
        glm::vec3  rotation; /** @brief Rotation vector. */
        glm::vec3 vitesse{ 0.0f,0.0f,0.0f }; /** @brief Velocity vector. */
        glm::vec3 acceleration{ 0.0f,0.0f,0.0f }; /** @brief Acceleration vector. */
        float friction = 1.0f; /** @brief Friction coefficient. */

        AABB colisionBox = AABB(); /** @brief Collision box. */

        /**
         * @brief Generates a 4x4 transformation matrix based on translation, scale, and rotation.
         * @return The transformation matrix.
        */
        glm::mat4 mat4();

        /**
         * @brief Generates a 3x3 normal matrix based on the inverse of the scale and rotation.
         * @return The normal matrix.
        */
        glm::mat3 normalMatrix();

        /**
         * @brief Sets the transformation with the provided translation and scale.
         * @param translation : The new translation vector.
         * @param scale : The new scale vector.
        */
        void setTransform(glm::vec3 translation, glm::vec3 scale);

        /**
         * @brief Sets the translation of the object.
         * @param translation : The new translation vector.
        */
        void setTranslation(glm::vec3 translation);

        /**
         * @brief Updates the position based on velocity.
        */
        void update();

        /**
         * @brief Updates acceleration and applies friction.
        */
        void updateAcceleration();

        /**
         * @brief Applies bouncing behavior to the object based on collision with a box.
         * @param box : The collision box.
        */
        void bouncingAABB(AABB box);
    };

    /**
     * @brief Structure representing the point light component of a game object.
    */
    struct PointLightComponent {
        float lightIntensity = 1.0f; /** @brief Intensity of the point light. */
    };

    /**
     * @brief Class representing a game object in the LVE engine.
    */
    class LveGameObject {
    public:
        using id_t = unsigned int; /** @brief Type alias for the object ID. */
        using Map = std::unordered_map<id_t, LveGameObject>; /** @brief Type alias for the object map. */

        /**
         * @brief Creates a new game object with a unique ID.
         * @return The newly created game object.
        */
        static LveGameObject createGameObject() { static id_t currentId = 0; return LveGameObject{ currentId++ }; }
        
        /**
         * @brief Creates a point light game object with the specified parameters.
         * @param intensity : The light intensity.
         * @param radius : The light radius.
         * @param color : The light color.
         * @return The created point light game object.
        */
        static LveGameObject makePointLight(float intensity = 10.f, float radius = 0.1f, glm::vec3 color = glm::vec3(1.f));

        LveGameObject(const LveGameObject&) = delete;
        LveGameObject& operator=(const LveGameObject&) = delete;
        LveGameObject(LveGameObject&&) = default;
        LveGameObject& operator=(LveGameObject&&) = default;

        /**
         * @brief Gets the ID of the game object.
         * @return The ID.
        */
        id_t getId() { return id; }

        /**
         * @brief Gets the minimum point of the bounding box.
         * @return The minimum point.
        */
        glm::vec3 get_point_box_min() { return { -transform.translation.x / 2, -transform.translation.y / 2, -transform.translation.z / 2 }; }
        
        /**
         * @brief Gets the maximum point of the bounding box.
         * @return The maximum point.
        */
        glm::vec3 get_point_box_max() { return { transform.translation.x / 2, transform.translation.y / 2, transform.translation.z / 2 }; }



        // ----------------- Variable -----------------
        std::shared_ptr<LveModel>model{}; /** @brief Pointer to the model associated with the game object. */
        glm::vec3 color{}; /** @brief Color of the game object. */
        TransformComponent transform{}; /** @brief Transformation component of the game object. */
        std::unique_ptr<PointLightComponent> pointLight = nullptr; /** @brief Pointer to the point light component. */


    private:
        /**
         * @brief Private constructor for creating a game object with a specified ID.
         * @param objId The ID of the game object.
        */
        LveGameObject(id_t objId) : id(objId) {}



        // ----------------- Variable -----------------
        id_t id; /** @brief ID of the game object. */
    };
}