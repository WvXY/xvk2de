#pragma once

#include "xev_device.hpp"
#include "xev_game_object.hpp"
#include "xev_renderer.hpp"
#include "xev_window.hpp"

#include <memory>
#include <string>
#include <vector>

namespace xev {
  class FirstApp {
  public:
    static constexpr int WIDTH = 1280;
    static constexpr int HEIGHT = 720;

    FirstApp();
    ~FirstApp();
    FirstApp(const FirstApp&) = delete;
    FirstApp& operator=(const FirstApp&) = delete;

    void run();

  private:
    XevWindow xevWindow{ "XenonApp", WIDTH, HEIGHT };
    XevDevice xevDevice{ xevWindow };
    XevRenderer xevRenderer{ xevWindow, xevDevice };

    void loadGameObjects();
    std::vector<XevGameObject> gameObjects;
  };
} // namespace xev
