#include "xev_app.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
  xev::XevApp app{};

  try {
    app.run();
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
