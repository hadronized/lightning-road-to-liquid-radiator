#ifndef __MOD1_HPP
#define __MOD1_HPP

#include "shader.hpp"

class mod1_c {
  /* shader stuff */
  /* tunnel program */
  shader_c _tunFS;
  shader_c _thunVS;
  program_c _tunP;
  /* thunders field program */
  shader_c _thunTCS;
  shader_c _thunTES;
  shader_c _thunGS;
  shader_c _thunFS;
  program_c _thunP;
  GLuint _thunders;
  void _init_thunders(void);

  /* uniforms stuff */
  GLint _tunTimeIndex;
  GLint _thunTimeIndex;
  void _init_uniforms();

public :
  mod1_c();
  ~mod1_c();

  void render(float time);
};

#endif /* guard */

