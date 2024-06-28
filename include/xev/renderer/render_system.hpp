#pragma once

#include "xev_device.hpp"
#include "xev_game_object.hpp"
#include "xev_pipeline.hpp"

// std
#include <memory>
#include <vector>

namespace xev {
class SimpleRenderSystem {
public:
  SimpleRenderSystem(XevDevice& device, VkRenderPass renderPass);
  ~SimpleRenderSystem();

  SimpleRenderSystem(const SimpleRenderSystem&)            = delete;
  SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

  void update(std::vector<XevGameObject>& gameObjects, float_t deltaTime);
  void render(VkCommandBuffer commandBuffer, std::vector<XevGameObject>& gameObjects);

private:
  void createPipelineLayout();
  void createPipeline(VkRenderPass renderPass);

  XevDevice& xevDevice;

  std::unique_ptr<XevPipeline> xevPipeline;
  VkPipelineLayout pipelineLayout;
};
} // namespace xev
