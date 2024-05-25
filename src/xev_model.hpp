#pragma once

#include "xev_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>

// std
#include <vector>

namespace xev {
  class XevModel {
  public:
    struct Vertex {
      glm::vec2 position;
      glm::vec3 color;

      static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
      static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
    };

    XevModel(XevDevice& device, const std::vector<Vertex>& vertices);
    ~XevModel();
    XevModel(const XevModel&) = delete;
    XevModel& operator=(const XevModel&) = delete;

    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);

  private:
    void createVertexBuffers(const std::vector<Vertex>& vertices);

    XevDevice& xevDevice;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;
  };
} // namespace xev
