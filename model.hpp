#pragma once

#include <_types/_uint32_t.h>

#include <cassert>
#include <glm/gtc/constants.hpp>

#include "device.hpp"
#include "vulkan/vulkan_core.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace ve {
  class Model {
  public:
    struct Vertex {
      glm::vec2 position;

      // getters
      static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
      static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
    };
    Model(Device &device, const std::vector<Vertex> &vertices);
    Model(const Model &src) = delete;
    Model &operator=(const Model &rhs) = delete;
    ~Model();
    static std::unique_ptr<Model> createCircleModel(Device &device, unsigned int numSides);
    static std::unique_ptr<Model> createSquareModel(Device &device, glm::vec2 offset);
    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);

  private:
    void createVertexBuffer(const std::vector<Vertex> &vertices);
    Device &device_;
    VkBuffer vertexBuffer_;
    VkDeviceMemory vertexBufferMemory_;
    uint32_t vertexCount_;
  };

}  // namespace ve