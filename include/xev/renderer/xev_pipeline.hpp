#pragma once

#include "xev_device.hpp"

#include <string>
#include <vector>

namespace xev {

struct PipelineConfigInfo {
  PipelineConfigInfo()                                     = default;
  PipelineConfigInfo(const PipelineConfigInfo&)            = delete;
  PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

  VkPipelineViewportStateCreateInfo viewportInfo;
  VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
  VkPipelineRasterizationStateCreateInfo rasterizationInfo;
  VkPipelineMultisampleStateCreateInfo multisampleInfo;
  VkPipelineColorBlendAttachmentState colorBlendAttachment;
  VkPipelineColorBlendStateCreateInfo colorBlendInfo;
  VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
  std::vector<VkDynamicState> dynamicStateEnables;
  VkPipelineDynamicStateCreateInfo dynamicStateInfo;
  VkPipelineLayout pipelineLayout = nullptr;
  VkRenderPass renderPass         = nullptr;
  uint32_t subpass                = 0;
};

class XevPipeline {
public:
  XevPipeline(
      XevDevice& device, const std::string& vertex_shader_path,
      const std::string& fragment_shader_path, const PipelineConfigInfo& configInfo);

  ~XevPipeline();

  XevPipeline(const XevPipeline&)            = delete;
  XevPipeline& operator=(const XevPipeline&) = delete;

  void bind(VkCommandBuffer commandBuffer);

  static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

private:
  static std::vector<char> readFile(const std::string& path);

  void createGraphicsPipeline(
      const std::string& vertex_shader_path, const std::string& fragment_shader_path,
      const PipelineConfigInfo& configInfo);

  void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

  XevDevice& xevDevice;
  VkPipeline graphicsPipeline;
  VkShaderModule vertShaderModule;
  VkShaderModule fragShaderModule;
};

} // namespace xev
