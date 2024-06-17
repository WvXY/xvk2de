// Bounding Box Test

#include "../src/common/xev_aliases.hpp"
#include "../src/math/primitive.hpp"
#include "../src/physics/AABB.hpp"
#include "../src/physics/physics.hpp"

#include <iostream>

namespace xet {

using namespace xev;
using namespace std;

void bbTest() {
  cout << "Running AABB tests..." << endl;

  AABB aabb1(vec2(0.f), vec2(2.f, 1.f));
  AABB aabb2(vec2(0.5f), vec2(1.5f, 2.f));

  AABB c = aabb1 + aabb2;
  cout << "c.max = " << c.max.x << ", " << c.max.y << "\t";
  cout << "c.min = " << c.min.x << ", " << c.min.y << "\n";
}

} // namespace xet (xe test)
