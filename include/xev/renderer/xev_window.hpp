#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <string>

// little game engine
namespace xev {
class XevWindow {
public:
  XevWindow(std::string windowName, int width, int height);
  ~XevWindow();
  XevWindow(const XevWindow&) = delete;
  XevWindow& operator=(const XevWindow&) = delete;

  bool shouldClose() { return glfwWindowShouldClose(window); }
  VkExtent2D getExtent() {
    return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
  }
  bool wasWindowResized() { return framebufferResized; }
  void resetWindowResizedFlag() { framebufferResized = false; }

  void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

  void diaplayOnTitle(std::string info) {
    std::string newWindowName = windowName + " - " + info;
    glfwSetWindowTitle(window, newWindowName.c_str());
  }

private:
  static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
  void initWindow();

  int width;
  int height;
  bool framebufferResized = false;
  std::string windowName;
  GLFWwindow* window{};
};
} // namespace xev
