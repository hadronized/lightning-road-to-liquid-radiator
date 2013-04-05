#ifndef __MATRIX_HPP
#define __MATRIX_HPP

struct mat4_c {
  float _[16];

  mat4_c(float *sub);
  ~mat4_c(void);
};

mat4_c gen_perspective(float fovy, float ratio, float znear, float zfar);

#endif /* guard */

