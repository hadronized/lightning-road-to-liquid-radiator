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
    std::cerr << "'" << path << "' can't be open" << std::endl;
    exit(1);
  }

  return ss.str();
}

