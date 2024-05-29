#pragma once

#include "xev_model.hpp"
#include "xev_settings.hpp"

// std
#include <memory>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace xev {
struct Transform2dComponent {
  glm::vec2 translation{};
  glm::vec2 scale{1.0f, 1.0f};
  float rotation{};

  glm::mat2 mat2() {
    const float c = glm::cos(rotation);
    const float s = glm::sin(rotation);
    glm::mat2 rotMat{{c, s}, {-s, c}};
    glm::mat2 scaleMat{scale.x, 0.0f, 0.0f, scale.y};
    return rotMat * scaleMat;
  }
};

class XevGameObject {
public:
  using id_t = unsigned int;

  static XevGameObject createGameObject() {
    static id_t currentId = 0;
    return XevGameObject{currentId++};
  }

  XevGameObject(const XevGameObject&)            = delete;
  XevGameObject& operator=(const XevGameObject&) = delete;
  XevGameObject(XevGameObject&&)                 = default;
  XevGameObject& operator=(XevGameObject&&)      = delete;

  [[nodiscard]] id_t getId() const { return id; }

  const id_t id{};
  std::shared_ptr<XevModel> model{};
  glm::vec3 color{};
  Transform2dComponent transform2d{};

  void update(float_t deltaTime) {
  }

  void fixedUpdate() { update(SEC_PER_UPDATE); }

private:
  explicit XevGameObject(id_t objId) : id{objId} {}
};
} // namespace xev
