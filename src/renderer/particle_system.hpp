#pragma once

#include "xev_device.hpp"
#include "xev_game_object.hpp"
#include "xev_pipeline.hpp"

// std
#include <memory>
#include <vector>

namespace xev {
class ParticleSystem {
public:
  ParticleSystem(XevDevice& device, VkRenderPass renderPass);
  ~ParticleSystem();

  ParticleSystem(const ParticleSystem&)            = delete;
  ParticleSystem& operator=(const ParticleSystem&) = delete;

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
