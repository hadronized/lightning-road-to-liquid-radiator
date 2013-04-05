#ifndef __MOD1_HPP
#define __MOD1_HPP

#include "shader.hpp"

class mod1_c {
  /* shader stuff */
  shader_c _stdFS;
  program_c _stdP;

  /* uniforms stuff */
  GLint _stdTimeIndex;
  void _init_uniforms();

public :
  mod1_c();
  ~mod1_c();

  void render(float time);
};

#endif /* guard */

