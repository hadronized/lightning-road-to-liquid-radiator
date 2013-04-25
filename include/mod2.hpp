#ifndef __MOD2_HPP
#define __MOD2_HPP

#include "shader.hpp"

class mod2_c {
  /* lava part */
  shader_c _stdFS;
  program_c _stdP;
  /* cube part */
  program_c &_cubeP;
  GLuint _cube;

  /* uniforms stuff */
  GLint _stdTimeIndex;
  GLint _stdRes;
  GLint _stdFovy;
  GLuint _cubeTimeIndex;

  void _init_uniforms();

public :
  mod2_c(program_c &cubeP, GLuint cube);
  ~mod2_c();

  void render(float time);
};

#endif /* guard */

