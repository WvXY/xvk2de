#include "particle_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

#ifndef PARTICLE_SIZE
#define PARTICLE_SIZE 0.1f
#endif

namespace xev {

struct PushData {
  vec2 position{0.f};
  float life{1.0f};
  float size{0.f};
  vec3 color{1.f};
};

ParticleSystem::ParticleSystem(XevDevice& device, VkRenderPass renderPass)
    : xevDevice{device} {
  createPipelineLayout();
  createPipeline(renderPass);
}

ParticleSystem::~ParticleSystem() {
  vkDestroyPipelineLayout(xevDevice.device(), pipelineLayout, nullptr);
}

void ParticleSystem::createPipelineLayout() {
  VkPushConstantRange pushConstantRange{};
  pushConstantRange.stageFlags =
      VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
  pushConstantRange.offset = 0;
  pushConstantRange.size   = sizeof(PushData);

  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType          = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0;
  pipelineLayoutInfo.pSetLayouts    = nullptr;
  pipelineLayoutInfo.pushConstantRangeCount = 1;
  pipelineLayoutInfo.pPushConstantRanges    = &pushConstantRange;
  if (vkCreatePipelineLayout(
          xevDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create pipeline layout!");
  }
}

//void ParticleSystem::getAttributeDescriptions(PipelineConfigInfo& configInfo) {
//  configInfo.attributeDescriptions = std::vector<VkVertexInputAttributeDescription>{};
//} // don't need any attributes

void ParticleSystem::createPipeline(VkRenderPass renderPass) {
  assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

  PipelineConfigInfo pipelineConfig{};
  XevPipeline::defaultPipelineConfigInfo(pipelineConfig);
  pipelineConfig.renderPass     = renderPass;
  pipelineConfig.pipelineLayout = pipelineLayout;
  xevPipeline                   = std::make_unique<XevPipeline>(
      xevDevice, "../shaders/particle.vert.spv", "../shaders/particle.frag.spv",
      pipelineConfig);
}

void ParticleSystem::update(
    std::vector<XevGameObject>& gameObjects, float_t deltaTime) {
  for (auto& go : gameObjects) {
    if (go.type == GameObjectType::Particle)
      go.update(deltaTime);
  }
}

void ParticleSystem::render(
    VkCommandBuffer commandBuffer, std::vector<XevGameObject>& gameObjects) {
  xevPipeline->bind(commandBuffer);

  for (auto& obj : gameObjects) {
    if (obj.type != GameObjectType::Particle) continue;
    PushData push{};
    push.position    = obj.transform.translation;
    push.color     = obj.color;
    push.size      = PARTICLE_SIZE;

    vkCmdPushConstants(
        commandBuffer, pipelineLayout,
        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0,
        sizeof(PushData), &push);
    obj.model->bind(commandBuffer);
    obj.model->draw(commandBuffer);
  }
}

} // namespace xev
