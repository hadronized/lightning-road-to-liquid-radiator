#ifndef __MOD3_HPP
#define __MOD3_HPP

#include "gl.hpp"
#include "shader.hpp"

namespace {
}

class mod3_c {
  /* shader stuff */
  shader_c _ppFS;
  program_c _ppP;

  /* uniforms stuff */
  GLint _ppRes;
  GLint _ppTime;
  void _init_uniforms();

public :
  mod3_c();
  ~mod3_c();

  void render(float time);
};

#endif /* guard */

