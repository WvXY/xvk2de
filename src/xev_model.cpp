#include "xev_model.hpp"

#include <cassert>
#include <cstring>

namespace xev {
  XevModel::XevModel(XevDevice& device, const std::vector<Vertex>& vertices)
    : xevDevice{ device } {
    createVertexBuffers(vertices);
  }

  XevModel::~XevModel() {
    vkDestroyBuffer(xevDevice.device(), vertexBuffer, nullptr);
    vkFreeMemory(xevDevice.device(), vertexBufferMemory, nullptr);
  }

  void XevModel::bind(VkCommandBuffer commandBuffer) {
    VkBuffer buffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
  }

  void XevModel::draw(VkCommandBuffer commandBuffer) {
    vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
  }

  void XevModel::createVertexBuffers(const std::vector<Vertex>& vertices) {
    vertexCount = static_cast<uint32_t>(vertices.size());
    assert(vertexCount >= 3 && "Vertex count must be at least 3");

    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;

    xevDevice.createBuffer(
      bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
      vertexBuffer, vertexBufferMemory);

    void* data;
    vkMapMemory(xevDevice.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(xevDevice.device(), vertexBufferMemory);
  }

  std::vector<VkVertexInputBindingDescription> XevModel::Vertex::getBindingDescriptions() {
    std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
    bindingDescriptions[0].binding = 0;
    bindingDescriptions[0].stride = sizeof(Vertex);
    bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return bindingDescriptions;
  }

  std::vector<VkVertexInputAttributeDescription>
    XevModel::Vertex::getAttributeDescriptions() {
    return {// location, binding, format, offset
            {0, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, position)},
            {1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color)} };
  }
} // namespace xev
