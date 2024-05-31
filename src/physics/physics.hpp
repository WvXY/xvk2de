#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "xev_aliases.hpp"
#include "xev_settings.hpp"
#include "AABB.hpp"

namespace xev {
template<typename T>
class MotionComponent {  // particle physics, only mass no size
public:
  MotionComponent() { init(); }
  MotionComponent(const T pos, const T vel, const T acc)
      : pos(pos), vel(vel), acc(acc) { init();}

  MotionComponent operator=(const MotionComponent&) = delete;
  ~MotionComponent() = default;

  void update(float deltaTime) {
    if (pos.y > 1) {
      pos.y = 1;
      vel.y = -vel.y * damping;
    } else if (pos.y < -1) {
      pos.y = -1;
      vel.y = -vel.y * damping;
    }
    if (pos.x > 1) {
      pos.x = 1;
      vel.x = -vel.x * damping;
    } else if (pos.x < -1) {
      pos.x = -1;
      vel.x = -vel.x * damping;
    }

//    if (atRest()) { return; }

    T velPrev = vel;
    vel += realAcc() * deltaTime;
    pos += (vel + velPrev) * 0.5f * deltaTime;
  }

  void init() {
    if (GRAVITY_MODE) {acc.y = -gravity;}
  }

  T pos{0.f};
  T vel{0.f};
  T acc{0.f};

  float damping = 0.99f;
  float airResistance = 0.4f;
  T velWind{0.f};

private:
  const float gravity = 9.8f;
  float mass = 1.0f;

  T inline realAcc() const { return acc + (velWind - vel) * airResistance / mass; }

  bool atRest() const { return glm::length(vel) < 0.001f; }
};
} // namespace xev