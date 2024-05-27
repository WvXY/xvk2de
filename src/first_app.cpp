#include "first_app.hpp"
#include "primitive.hpp"
#include "render_system.hpp"

#include <chrono>

// std
#include <array>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <thread>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#define MS_PER_FRAME 1000.0f / 60.0f

namespace xev {

struct SimplePushConstantData {
  glm::mat2 transform{1.0f};
  glm::vec2 offset;
  alignas(16) glm::vec3 color;
};

FirstApp::FirstApp() {
  loadGameObjects();
}

FirstApp::~FirstApp() {}

void FirstApp::run() {
  SimpleRenderSystem simpleRenderSystem{xevDevice, xevRenderer.getSwapChainRenderPass()};

  auto lastFrameTime    = std::chrono::high_resolution_clock::now();
  auto nFramesTime      = std::chrono::high_resolution_clock::now();
  constexpr int nFrames = 10;
  int64_t frameCount    = 0;

  while (!xevWindow.shouldClose()) {

    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime =
        std::chrono::duration<float_t>(currentTime - lastFrameTime).count();
    lastFrameTime = currentTime;

    // update and render
    glfwPollEvents();
    if (auto commandBuffer = xevRenderer.beginFrame()) {
      xevRenderer.beginSwapChainRenderPass(commandBuffer);
      simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
      xevRenderer.endSwapChainRenderPass(commandBuffer);
      xevRenderer.endFrame();
    }

    // Frame rate
    if (frameCount % nFrames == 0) {
      auto nFramesDur = std::chrono::duration<float_t>(currentTime - nFramesTime).count();
      std::string info = "FPS: " + std::to_string(nFrames / nFramesDur);
      xevWindow.diaplayOnTitle(info);
      nFramesTime     = currentTime;
    }
    auto timeToSleep = MS_PER_FRAME - elapsedTime * 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeToSleep)));
  }

  vkDeviceWaitIdle(xevDevice.device());
}

void FirstApp::loadGameObjects() {
  // std::vector<XevModel::Vertex> vertices{
  //     {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
  //     {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
  //     {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
  // auto xevModel = std::make_shared<XevModel>(xevDevice, vertices);

  // for (int i = 0; i < 1; i++) {
  // auto triangle  = XevGameObject::createGameObject();
  // triangle.model = xevModel;
  // // triangle.color = glm::vec3(1.0f * sin(i), 1.f * cos(i), 1.0f * sin(i * 0.5f));
  // // triangle.transform2d.translation.x = 0.0f;
  // triangle.transform2d.scale    = glm::vec2(.5f);
  // triangle.transform2d.rotation = glm::two_pi<float>() * 0.25f;

  Box box({0, 0}, 0.5f, 0.5f);
  auto bv                                = box.vertices();
  std::vector<XevModel::Vertex> vertices = {
      {{bv[0].x, bv[0].y}, {1.0f, 0.0f, 0.0f}},
      {{bv[1].x, bv[1].y}, {0.0f, 1.0f, 0.0f}},
      {{bv[2].x, bv[2].y}, {0.0f, 0.0f, 1.0f}},
      {{bv[3].x, bv[3].y}, {1.0f, 1.0f, 0.0f}},
  };
  const std::vector<uint32_t> indices = {0, 1, 2, 0, 2, 3, 1};

  auto boxModel = std::make_shared<XevModel>(xevDevice, vertices, indices);
  auto gbox     = XevGameObject::createGameObject();
  gbox.model    = boxModel;

  gameObjects.push_back(std::move(gbox));
  // }
}

} // namespace xev
