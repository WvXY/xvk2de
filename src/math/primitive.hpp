#pragma once

#include <utility>
#include <vector>

#include "xev_aliases.hpp"

namespace xev {

// class Particle {
//   vec2 position{0.f};
// };

class Ray {
public:
  vec2 dir{1.f, 0.f};
  vec2 ori{0.f};

  Ray(const vec2 dir, const vec2 ori) : dir(dir), ori(ori) {}
  Ray() = default;
};

class Box {
public:
  Box(const vec2 center, const float width, const float height)
      : min(center - vec2(width / 2, height / 2)),
        max(center + vec2(width / 2, height / 2)) {}
  Box(vec2 min, vec2 max) : min(min), max(max) {}
  Box() : min(0.f), max(1.f) {}

  std::vector<vec2> getVertices() const {
    return {
        vec2{min.x, min.y}, vec2{max.x, min.y}, vec2{max.x, max.y}, vec2{min.x, max.y}};
  }

private:
  vec2 min{};
  vec2 max{};
};

class Circle {
public:
  Circle(const vec2 center, const float radius) : center(center), radius(radius) {}
  Circle() : center(0.f), radius(0.f) {}
  ~Circle() = default;

private:
  vec2 center{};
  float radius{};
};

class Polygon {
  std::vector<vec2> vertices;
  std::vector<uint32_t> indices;  // optional
};

} // namespace xev
