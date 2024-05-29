#include "xev_app.hpp"
#include "primitive.hpp"
#include "render_system.hpp"
#include "xev_settings.hpp"

// std
#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace xev {

struct SimplePushConstantData {
  glm::mat2 transform{1.0f};
  glm::vec2 offset;
  alignas(16) glm::vec3 color;
};

XevApp::XevApp() {
  loadGameObjects();
}

XevApp::~XevApp() {}

void XevApp::run() {
  SimpleRenderSystem simpleRenderSystem{xevDevice, xevRenderer.getSwapChainRenderPass()};

  auto prevTime         = std::chrono::high_resolution_clock::now();
  auto nFramesTime      = std::chrono::high_resolution_clock::now();
  constexpr int nFrames = 100;
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

      //      for (; timeLag > SEC_PER_UPDATE; timeLag -= SEC_PER_UPDATE) // Fixed time
      //      step
      //        simpleRenderSystem.updateGameObjects(gameObjects, SEC_PER_UPDATE);
      simpleRenderSystem.updateGameObjects(gameObjects, dt);

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
    //    // Frame rate control
    //     auto timeToSleep = MS_PER_FRAME - dt * 1000;
    //     std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeToSleep)));
  }

  vkDeviceWaitIdle(xevDevice.device());
}

void XevApp::loadGameObjects() {
//    {
//      std::vector<XevModel::Vertex> vertices{
//          {{0.0f, -0.8f}, {1.0f, 0.0f, 0.0f}},
//          {{0.5f, 0.2f}, {0.0f, 1.0f, 0.0f}},
//          {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
//      auto xevModel = std::make_shared<XevModel>(xevDevice, vertices);
//
//      for (int i = 0; i < 4; i++) {
//        auto triangle  = XevGameObject::createGameObject();
//        triangle.model = xevModel;
//        triangle.transform.translation.y = 0.5f * i;
//        triangle.transform.translation.x = 0.0f;
//        triangle.transform.scale         = glm::vec2(.5f);
//        triangle.transform.rotation      = glm::two_pi<float>() * 0.25f;
//        triangle.physics.acc.x = 1.f;
//        gameObjects.push_back(std::move(triangle));
//      }
//    }

  Box box({0, 0}, 0.4f, 0.4f);
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
    gbox.physics.acc.x = 1.f;
    gbox.physics.velWind = {2.f, 24.f};

  gameObjects.push_back(std::move(gbox));
  // }
}

} // namespace xev
