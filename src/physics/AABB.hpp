#pragma once

#include "xev_aliases.hpp"
#include <glm/glm.hpp>

namespace xev {

template<typename T>
struct AABB {
  AABB() = default;
  AABB(const T& min, const T& max) : min(min), max(max) {}

  T min{};
  T max{};
};

}