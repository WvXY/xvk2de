#pragma once

#include <utility>
#include <vector>

#include "xev_aliases.hpp"

namespace xev {

// struct GameObject {
//   vec2 position{};
//   vec2 velocity{};
//   vec2 acceleration{};
//   float mass    = 1.f;
//   float damping = 1.f;
// };

struct Particle {
  vec2 position{};
  vec2 velocity{};
  vec2 acceleration{};
  float mass    = 1.f;
  float damping = 0.99f;
};

struct Box {
  vec2 min{};
  vec2 max{};

  Box(const vec2 center, const float width, const float height)
      : min(center - vec2(width / 2, height / 2)),
        max(center + vec2(width / 2, height / 2)) {}
  Box(vec2 min, vec2 max) : min(min), max(max) {}
  Box() : min(0.f), max(1.f) {}

  std::vector<vec2> vertices() const {
    return {
        vec2{min.x, min.y}, vec2{max.x, min.y}, vec2{max.x, max.y}, vec2{min.x, max.y}};
  }
};

struct Circle {
  vec2 center{};
  float radius{};

  Circle(const vec2 center, const float radius) : center(center), radius(radius) {}
  Circle() : center(0.f), radius(0.f) {}
};

struct Polygon {
  std::vector<vec2> vertices;
  std::vector<uint32_t> indices;  // optional
};

} // namespace xev
