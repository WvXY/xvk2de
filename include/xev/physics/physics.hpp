#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "AABB.hpp"
#include "xev_aliases.hpp"
#include "xev_settings.hpp"

namespace xev {

template <typename T> class MotionComponent { // particle physics, only mass no size
public:
  MotionComponent() = default;
  MotionComponent(const T pos) : pos(pos) {}
  MotionComponent(const T pos, const T vel) : pos(pos), vel(vel) {}

  MotionComponent operator=(const MotionComponent&) = delete;
  ~MotionComponent()                                = default;

  void update(float deltaTime) {
    if (atRest()) { return; }

    detectCollision();

    T velPrev = vel;
    vel += computeAcceleration() * deltaTime;
    pos += (vel + velPrev) * 0.5f * deltaTime;
  }

  // setters
  void addForce(const T& f) { force += f; }
  void setWind(const T& vel) { windVel = vel; }
  void setMass(const float m) { mass_inv = 1.f / m; }
  void setPos(const T& p) { pos = p; }
  void setGravity(const float_t new_gravity) { gravity = new_gravity; }
  void setVelocity(const T& v) { vel = v; }

  // getters
  T getPosition() const { return pos; }
  T getVelocity() const { return vel; }
  T getForce() const { return force; }

  T computeAcceleration() {
    acc = force * mass_inv + (windVel - vel) * airResistance * mass_inv;
    if (GRAVITY_MODE) { acc.y -= gravity; }
    return acc;
  }

private:
  T pos{0.f};
  T vel{0.f};
  T acc{0.f};
  T force{0.f};
  T windVel{0.f};

  float damping       = 0.99f;
  float airResistance = 0.3f;
  float gravity       = 9.8f; // m/s^2
  float mass_inv      = 1.0f; // inverse mass

  bool atRest() const {
    // There are 4 conditions for particle to be at rest
    // 1. velocity is nearly zero
    // 2. object touches an object
    // 3. force is zero or direction is opposite to the normal
    // 4. object is out of bounds
    return glm::length(vel) < 0.001f && (abs(pos.y) > 0.99f || abs(pos.x) > 0.99f);
  }

  void detectCollision() {
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
  }
};
} // namespace xev