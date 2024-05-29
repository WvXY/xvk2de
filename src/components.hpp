#pragma once

#include "xev_aliases.hpp"

namespace xev {
class MotionComponent {
public:
  vec2 getPosition() const { return pos; }
  vec2 getVelocity() const { return vel; }
  vec2 getAcceleration() const { return acc; }
  // TODO: use template

private:
  vec2 pos{0.f};
  vec2 vel{0.f};
  vec2 acc{0.f};
};
} // namespace xev