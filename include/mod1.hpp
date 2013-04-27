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

  /* thunders blur program */
  shader_c _thunBlurFS;
  program_c _thunBlurP;

  /* offscreen */ 
  GLuint _offtex;
  GLuint _rdbf;
  GLuint _fbo;
  void _setup_offscreen(void);

  /* uniforms stuff */
  GLint _tunTimeIndex;
  GLint _thunTimeIndex;
  void _init_uniforms(void);

  void _init_tessellation(void);

public :
  mod1_c(void);
  ~mod1_c(void);

  void render(float time);
};

#endif /* guard */

