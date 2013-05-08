#ifndef __MOD2_HPP
#define __MOD2_HPP

#include "shader.hpp"
#include "text_writer.hpp"

class mod2_c {
  /* text writer */
  text_writer_c &_textWriter;

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

  /* RGBA distor */
  shader_c _rgbaFS;
  program_c _rgbaP;
  GLuint _rgbaTimeIndex;

  /* offtex */
  GLuint _offtex;
  GLuint _rdbf;
  GLuint _fbo;

  void _setup_offscreen(float width, float height);
  void _init_uniforms(float width, float height);

public :
  mod2_c(float width, float height, text_writer_c &writer, program_c &cubeP, GLuint cube);
  ~mod2_c();

  void render(float time);
};

#endif /* guard */

