#pragma once

#include <utility>
#include <vector>

#include "xev_aliases.hpp"

namespace xev {

class Particle {
public:
  vec2 position{0.f};
  Particle() = default;
  explicit Particle(const vec2& pos) : position(pos) {}
};

} // namespace xev