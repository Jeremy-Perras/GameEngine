#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "model.hpp"
namespace ve {
  class GameObject {
    struct TransformComponent {
      glm::vec3 translation{};  // (position offset)
      glm::vec3 scale{1.F, 1.F, 1.0F};
      glm::vec3 rotation;

      glm::mat4 mat4() {
        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.x);
        const float s2 = glm::sin(rotation.x);
        const float c1 = glm::cos(rotation.y);
        const float s1 = glm::sin(rotation.y);
        return glm::mat4{{
                             scale.x * (c1 * c3 + s1 * s2 * s3),
                             scale.x * (c2 * s3),
                             scale.x * (c1 * s2 * s3 - c3 * s1),
                             0.0F,
                         },
                         {
                             scale.y * (c3 * s1 * s2 - c1 * s3),
                             scale.y * (c2 * c3),
                             scale.y * (c1 * c3 * s2 + s1 * s3),
                             0.0F,
                         },
                         {
                             scale.z * (c2 * s1),
                             scale.z * (-s2),
                             scale.z * (c1 * c2),
                             0.0F,
                         },
                         {translation.x, translation.y, translation.z, 1.0F}};
      }
    };

  public:
    using id_t = unsigned int;

    GameObject(const GameObject &) = delete;
    GameObject &operator=(const GameObject &) = delete;
    GameObject(GameObject &&) = default;
    GameObject &operator=(GameObject &&) = default;
    ~GameObject(){};

    static GameObject createGameObject() {
      static id_t currentId = 0;
      return GameObject(currentId++);
    }

    std::shared_ptr<Model> model{};
    glm::vec3 color{};
    TransformComponent transform{};

    // Getter
    id_t getId() const { return id_; }

  private:
    GameObject(id_t objId) : id_{objId} {};

    id_t id_;
  };
}  // namespace ve