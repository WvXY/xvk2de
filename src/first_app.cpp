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

#define MS_PER_FRAME 1000.0f / 600.0f // Max 600 fps
#define SEC_PER_UPDATE 1.0f / 100.0f  // 100 updates per second

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

  auto prevTime         = std::chrono::high_resolution_clock::now();
  auto nFramesTime      = std::chrono::high_resolution_clock::now();
  constexpr int nFrames = 10;
  float_t timeLag       = 0.0f;
  int64_t frameCount    = 0;

  while (!xevWindow.shouldClose()) {
    glfwPollEvents();

    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto dt          = std::chrono::duration<float_t>(currentTime - prevTime).count();
    prevTime         = currentTime;
    timeLag += dt; // in seconds

    // update and render
    if (auto commandBuffer = xevRenderer.beginFrame()) {
      xevRenderer.beginSwapChainRenderPass(commandBuffer);

      for (; timeLag > SEC_PER_UPDATE; timeLag -= SEC_PER_UPDATE) // Fixed time step
        simpleRenderSystem.updateGameObjects(gameObjects, SEC_PER_UPDATE);

      simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
      xevRenderer.endSwapChainRenderPass(commandBuffer);
      xevRenderer.endFrame();
    }

    if (frameCount % nFrames == 0) {
      auto nFramesDur = std::chrono::duration<float_t>(currentTime - nFramesTime).count();
      std::string info = "FPS: " + std::to_string(nFrames / nFramesDur);
      xevWindow.diaplayOnTitle(info);
      nFramesTime = currentTime;
    }
    // Frame rate control
    // auto timeToSleep = MS_PER_FRAME - elapsedTime * 1000;
    // std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeToSleep)));
  }

  vkDeviceWaitIdle(xevDevice.device());
}

void FirstApp::loadGameObjects() {
  {
    std::vector<XevModel::Vertex> vertices{
        {{0.0f, -0.8f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.2f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
    auto xevModel = std::make_shared<XevModel>(xevDevice, vertices);

    for (int i = 0; i < 4; i++) {
      auto triangle  = XevGameObject::createGameObject();
      triangle.model = xevModel;
      // triangle.color = glm::vec3(1.0f * sin(i), 1.f * cos(i), 1.0f * sin(i * 0.5f));
      triangle.transform2d.translation.y = 0.5f * i;
      triangle.transform2d.translation.x = 0.0f;
      triangle.transform2d.scale         = glm::vec2(.5f);
      triangle.transform2d.rotation      = glm::two_pi<float>() * 0.25f;
      gameObjects.push_back(std::move(triangle));
    }
  }

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
