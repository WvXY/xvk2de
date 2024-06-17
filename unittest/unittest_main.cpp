#include "bb_test.cpp"
#include "geo_test.cpp"

using namespace xet;

int main(int argc, char** argv) {
  std::cout << "Running tests..." << std::endl;

  bbTest();
  geoTest();
}