#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

#ifndef EPSILON
#define EPSILON 1e-3
#endif

namespace xev {

float_t norm(const auto& x) {
  // return glm::sqrt(glm::dot(x, x));
  return glm::length(x);
}

auto normalize(const auto& x) {
  return glm::normalize(x);
}

auto cmp_float(const auto& x, const auto& y) {
  return glm::epsilonEqual(x, y, EPSILON);
}


} // namespace xem : Xev Engine Math