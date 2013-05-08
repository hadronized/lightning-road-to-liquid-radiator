#include <iostream>
#include <cstdlib>
#include "bootstrap.hpp"

int main(int argc, char **argv) {
  float width;
  float height;
  bool full = false;

  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " WIDTH HEIGHT [FULL]" << std::endl;
    return 1;
  }
  width = std::atoi(argv[1]);
  height = std::atoi(argv[2]);
  if (argc == 4 && *argv[3] == 'f')
    full = true;
  std::cout << "Width: " << width << std::endl << "Height: " << height << std::endl << "Full: " << (full ? "on" : "off") << std::endl;
  bootstrap_c boot(width, height, full);

  boot.init();
  boot.run();
  return 0;
}
