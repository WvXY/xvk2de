#include "../../src/xev_app.hpp"
#include "particle_system.hpp"
#include "primitive.hpp"
#include "particle.hpp"
#include "render_system.hpp"
#include "xev_settings.hpp"


namespace xev {
class Ballistic : public XevApp {
public:
  void run() {
    SimpleRenderSystem simpleRenderSystem{xevDevice, xevRenderer.getSwapChainRenderPass()};
    ParticleSystem particleSystem{xevDevice, xevRenderer.getSwapChainRenderPass()};

    while (!xevWindow.shouldClose()) {
      glfwPollEvents();

      // update and render
      if (auto commandBuffer = xevRenderer.beginFrame()) {
        xevRenderer.beginSwapChainRenderPass(commandBuffer);
      };

      vkDeviceWaitIdle(xevDevice.device());
    }
  }
};


}

int main() {
  xev::Ballistic ballistic;
  ballistic.run();
}