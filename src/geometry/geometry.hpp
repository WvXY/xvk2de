#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>

// #include "xev_math.hpp"
#include <typeinfo>

#define EPSILON 1e-3

namespace xev {

// ============================================================================
// distances functions
float_t distPointToPoint(const auto& p, const auto& q) {
  return glm::length(p - q);
}

float_t distPointTo_(const auto& x, const auto& normal, const auto& point) {
  return glm::abs(glm::dot(point - x, glm::normalize(normal)));
}

float_t
distPointToPlane(const auto& point, const auto& planeNormal, const auto& planePoint) {
  return distPointTo_(point, planeNormal, planePoint);
}

float_t distPointToLine();

bool isPointOnPlane(const auto& point, const auto& planeNormal, const auto& planePoint) {
  assert(
      typeid(point) == typeid(planeNormal) && typeid(planeNormal) == typeid(planePoint));
  return distPointTo_(point, planeNormal, planePoint) < EPSILON;
}

// ============================================================================
// area

inline float_t
triangleSize3(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2) {
  return glm::length(cross(p1 - p0, p2 - p0)) / 2.f;
}

inline float_t
triangleArea2(const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2) {
  glm::vec2 v0 = p1 - p0, v1 = p2 - p0;
  return glm::abs(v0.x * v1.y - v0.y * v1.x) / 2.0f;
}

// ============================================================================

inline glm::vec3
getNormal(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2) {
  return normalize(cross(p1 - p0, p2 - p0));
}

} // namespace xev
