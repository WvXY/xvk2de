#include "geometry.hpp"
#include "xev_aliases.hpp"

#include <iostream>

using namespace xev;
using namespace std;

int main() {
  cout << "test" << endl;

  vec3 p = {0.f, 0.f, 0.f};
  vec3 nrm = {1.f, 1.f, 0.f};
  vec3 pnt = {1.f, 1.f, 0.f};
  auto dist = distancePointTo_<float_t>(p, nrm, pnt);
  cout << dist << endl;
  cout << isPointOnPlane(p, nrm, pnt) << endl;

}