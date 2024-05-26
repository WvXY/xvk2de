#include "xev_model.hpp"

#include <cassert>
#include <cstring>

namespace xev {
XevModel::XevModel(XevDevice& device, const std::vector<Vertex>& vertices)
    : xevDevice{device} {
  createVertexBuffers(vertices);
}

XevModel::XevModel(
    XevDevice& device, const std::vector<Vertex>& vertices,
    const std::vector<uint32_t>& indices)
    : xevDevice{device}, hasIndexBuffer{true} {
  createVertexBuffers(vertices);
  createIndexBuffers(indices);
}

XevModel::~XevModel() {
  vkDestroyBuffer(xevDevice.device(), vertexBuffer, nullptr);
  vkFreeMemory(xevDevice.device(), vertexBufferMemory, nullptr);
  vkDestroyBuffer(xevDevice.device(), indexBuffer, nullptr);
  vkFreeMemory(xevDevice.device(), indexBufferMemory, nullptr);
}

void XevModel::bind(VkCommandBuffer commandBuffer) {
  VkBuffer buffers[]     = {vertexBuffer};
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
  if (hasIndexBuffer)
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
}

void XevModel::draw(VkCommandBuffer commandBuffer) {
  if (hasIndexBuffer) {
    vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
  } else {
    vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
  }
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

void XevModel::createIndexBuffers(const std::vector<uint32_t>& indices) {
  indexCount              = static_cast<uint32_t>(indices.size());
  VkDeviceSize bufferSize = sizeof(indices[0]) * indexCount;

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  xevDevice.createBuffer(
      bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
      stagingBuffer, stagingBufferMemory);

  void* data;
  vkMapMemory(xevDevice.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, indices.data(), (size_t)bufferSize);
  vkUnmapMemory(xevDevice.device(), stagingBufferMemory);

  xevDevice.createBuffer(
      bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

  xevDevice.copyBuffer(stagingBuffer, indexBuffer, bufferSize);

  vkDestroyBuffer(xevDevice.device(), stagingBuffer, nullptr);
  vkFreeMemory(xevDevice.device(), stagingBufferMemory, nullptr);
}

std::vector<VkVertexInputBindingDescription> XevModel::Vertex::getBindingDescriptions() {
  std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
  bindingDescriptions[0].binding   = 0;
  bindingDescriptions[0].stride    = sizeof(Vertex);
  bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  return bindingDescriptions;
}

std::vector<VkVertexInputAttributeDescription>
XevModel::Vertex::getAttributeDescriptions() {
  return {// location, binding, format, offset
          {0, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, position)},
          {1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color)}};
}
} // namespace xev
