#include <fstream>
#include <sstream>
#include "common.hpp"

std::string load_source(std::string const &path) {
  std::ifstream fh;
  std::stringstream ss;

  fh.open(path);
  if (fh) {
    ss << fh.rdbuf();
    fh.close();
  } else {
    throw ("file not found: " + path);
  }

  return ss.str();
}

