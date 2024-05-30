#pragma once

#include "xev_aliases.hpp"
#include "xev_settings.hpp"
#include <glm/glm.hpp>
#include "glm/ext.hpp"

namespace xev {

template <typename T>
T inline distancePointTo_(const auto& x, const auto& normal, const auto& point) {
  return static_cast<T>(glm::abs(glm::dot((point - x), glm::normalize(normal))));
}

template <typename T>
T distancePointToPlane(const auto& point, const auto& planeNormal, const auto& planePoint) {
  return distancePointTo_<T>(point, planeNormal, planePoint);
}

template <typename T>
T distancePointToLine();

bool isPointOnPlane(const auto& point, const auto& planeNormal, const auto& planePoint) {
  assert(typeid(point) == typeid(planeNormal) && typeid(planeNormal) == typeid(planePoint));
  return distancePointTo_<float_t>(point, planeNormal, planePoint) < EPSILON;
}

} // namespace xeg : Xenon Engine Geometry
