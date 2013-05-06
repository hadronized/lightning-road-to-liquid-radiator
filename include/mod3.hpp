#ifndef __MOD3_HPP
#define __MOD3_HPP

#include "gl.hpp"
#include "shader.hpp"
#include "text_writer.hpp"

namespace {
}

class mod3_c {
  /* text writer */
  /* TODO: to move away */
  text_writer_c _writer;

  /* shader stuff */
  shader_c _ppFS;
  program_c _ppP;

  /* uniforms stuff */
  void _init_uniforms();

public :
  mod3_c();
  ~mod3_c();

  void render(float time);
};

#endif /* guard */

