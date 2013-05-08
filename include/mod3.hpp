#ifndef __MOD3_HPP
#define __MOD3_HPP

#include "gl.hpp"
#include "shader.hpp"
#include "text_writer.hpp"

class mod3_c {
  /* text writer */
  text_writer_c &_writer;

  /* offscreen */
  GLuint _offtex;
  GLuint _rdbf;
  GLuint _fbo;

  /* plasma shader! */
  shader_c _plasmaFS;
  program_c _plasmaSP;

  /* uniforms */
  GLint _plasmaTimeIndex;

  void _init_shader(void);
  void _init_offscreen(float width, float height);
  void _init_uniforms(float width, float heihgt);

public :
  mod3_c(float width, float height, text_writer_c &writer);
  ~mod3_c();

  void render(float time);
};

#endif /* guard */

