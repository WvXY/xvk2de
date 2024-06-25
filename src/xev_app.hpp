#pragma once

#include "common/xev_game_object.hpp"
#include "xev_device.hpp"
#include "xev_renderer.hpp"
#include "xev_window.hpp"
#include "render_system.hpp"
#include "particle_system.hpp"

#include <memory>
#include <string>
#include <vector>

namespace xev {
class XevApp {
public:
  static constexpr int WIDTH  = 1280;
  static constexpr int HEIGHT = 720;

  XevApp();
  ~XevApp();
  XevApp(const XevApp&)            = delete;
  XevApp& operator=(const XevApp&) = delete;

  void run();

protected:
  XevWindow xevWindow{"XenonApp", WIDTH, HEIGHT};
  XevDevice xevDevice{xevWindow};
  XevRenderer xevRenderer{xevWindow, xevDevice};

  // SimpleRenderSystem simpleRenderSystem{xevDevice, xevRenderer.getSwapChainRenderPass()};
  // ParticleSystem particleSystem{xevDevice, xevRenderer.getSwapChainRenderPass()};

  void step();
  void loadGameObjects();
  std::vector<XevGameObject> gameObjects;
};
} // namespace xev
