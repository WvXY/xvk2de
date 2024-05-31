#include "geometry.hpp"
#include "xev_aliases.hpp"

#include <iostream>

using namespace xev;
using namespace std;

int main() {
  cout << "test" << endl;

  vec3 p    = {0.f, 0.f, 0.f};
  vec3 nrm  = {1.f, 1.f, 0.f};
  vec3 pnt  = {1.f, 1.f, 0.f};
  auto dist = distPointToPlane(p, nrm, pnt);
  cout << dist << endl;
  cout << isPointOnPlane(p, nrm, pnt) << endl;

  vec2 p0   = {0.f, 0.f};
  vec2 p1   = {1.f, 0.f};
  vec2 p2   = {0.f, 1.f};
  auto size = triangleArea2(p0, p1, p2);
  cout << size << endl;

  vec3 q0    = {0.f, 0.f, 1.f};
  vec3 q1    = {1.f, 0.f, 0.f};
  vec3 q2    = {0.f, 1.f, 0.f};
  auto size3 = triangleSize3(q0, q1, q2);
  cout << size3 << endl;
}