#pragma once

#include "xev_aliases.hpp"
#include <glm/glm.hpp>

namespace xev {

template<typename T>
struct AABB {
  AABB() = default;
  AABB(const T& min, const T& max) : min(min), max(max) {}

  AABB operator+(const AABB& other) const {
    AABB result;
    result.max = glm::max(this->max, other.max);
    result.min = glm::min(this->min, other.min);
    return result;
  }

  T min{};
  T max{};
};

}