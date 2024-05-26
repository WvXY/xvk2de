#pragma once

#include "xev_device.hpp"
#include "xev_swap_chain.hpp"
#include "xev_window.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace xev {
class XevRenderer {
public:
  XevRenderer(XevWindow& window, XevDevice& device);
  ~XevRenderer();
  XevRenderer(const XevRenderer&)            = delete;
  XevRenderer& operator=(const XevRenderer&) = delete;

  VkRenderPass getSwapChainRenderPass() const { return xevSwapChain->getRenderPass(); }
  bool isFrameInProgress() const { return isFrameStarted; }

  VkCommandBuffer getCurrentCommandBuffer() const {
    assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
    return commandBuffers[currentFrameIndex];
  }

  int getFrameIndex() const {
    assert(isFrameStarted && "Cannot get frame index when frame not in progress");
    return currentFrameIndex;
  }

  VkCommandBuffer beginFrame();
  void endFrame();
  void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
  void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

private:
  void createCommandBuffers();
  void freeCommandBuffers();
  void recreateSwapChain();

  XevWindow& xevWindow;
  XevDevice& xevDevice;
  std::unique_ptr<XevSwapChain> xevSwapChain;
  std::vector<VkCommandBuffer> commandBuffers;

  uint32_t currentImageIndex{0};
  int currentFrameIndex{0};
  bool isFrameStarted{false};
};
} // namespace xev
