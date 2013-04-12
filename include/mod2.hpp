#ifndef __MOD2_HPP
#define __MOD2_HPP

#include "shader.hpp"

class mod2_c {
  /* shader stuff */
  program_c _stpVS;
  shader_c _stdFS;
  program_c _stdP;

  /* uniforms stuff */
  GLint _stdTimeIndex;
  GLint _stdRes;
  GLint _stdFovy;
  void _init_uniforms();

public :
  mod2_c();
  ~mod2_c();

  void render(float time);
};

#endif /* guard */

