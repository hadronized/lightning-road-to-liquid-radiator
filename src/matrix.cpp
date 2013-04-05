#include <algorithm>
#include "matrix.hpp"

mat4_c::mat4_c(float *sub) {
  std::copy(sub, sub+16, _);
}

mat4_c::~mat4_c() {
}

mat4_c gen_perspective(float fovy, float ratio, float znear, float zfar) {
  float itanfovy = 1.f / tan(fovy / 2);
  float itanfovyr = itanfovy / ratio;
  float inf = 1.f / (znear - zfar);
  float nfinf = (znear + zfar) * inf;
  float m[] = {
    itanfovyr,      0.f,   0.f,  0.f,
          0.f, itanfovy,   0.f,  0.f,
          0.f,      0.f,   inf, -1.f,
          0.f,      0.f, nfinf,  1.f
  };

  return mat4_c(m);
}

