#include "render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

namespace xev {

struct SimplePushConstantData {
  glm::mat2 transform{1.f};
  glm::vec2 offset;
  alignas(16) glm::vec3 color;
};

SimpleRenderSystem::SimpleRenderSystem(XevDevice& device, VkRenderPass renderPass)
    : xevDevice{device} {
  createPipelineLayout();
  createPipeline(renderPass);
}

SimpleRenderSystem::~SimpleRenderSystem() {
  vkDestroyPipelineLayout(xevDevice.device(), pipelineLayout, nullptr);
}

void SimpleRenderSystem::createPipelineLayout() {
  VkPushConstantRange pushConstantRange{};
  pushConstantRange.stageFlags =
      VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
  pushConstantRange.offset = 0;
  pushConstantRange.size   = sizeof(SimplePushConstantData);

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

void SimpleRenderSystem::createPipeline(VkRenderPass renderPass) {
  assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

  PipelineConfigInfo pipelineConfig{};
  XevPipeline::defaultPipelineConfigInfo(pipelineConfig);
  pipelineConfig.renderPass     = renderPass;
  pipelineConfig.pipelineLayout = pipelineLayout;
  xevPipeline                   = std::make_unique<XevPipeline>(
      xevDevice, "../shaders/simple_shader.vert.spv", "../shaders/simple_shader.frag.spv",
      pipelineConfig);
}

void SimpleRenderSystem::updateGameObjects(
  std::vector<XevGameObject>& gameObjects, float_t deltaTime) {
    for (auto& obj : gameObjects) {
      obj.transform2d.rotation =
          glm::mod(obj.transform2d.rotation + deltaTime, glm::two_pi<float>());
      obj.transform2d.translation.x += 0.1f * deltaTime;
    }
}

void SimpleRenderSystem::renderGameObjects(
    VkCommandBuffer commandBuffer, std::vector<XevGameObject>& gameObjects) {
  xevPipeline->bind(commandBuffer);

  for (auto& obj : gameObjects) {
    SimplePushConstantData push{};
    push.offset    = obj.transform2d.translation;
    push.color     = obj.color;
    push.transform = obj.transform2d.mat2();

    vkCmdPushConstants(
        commandBuffer, pipelineLayout,
        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0,
        sizeof(SimplePushConstantData), &push);
    obj.model->bind(commandBuffer);
    obj.model->draw(commandBuffer);
  }
}

} // namespace xev
