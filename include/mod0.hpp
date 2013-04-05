#ifndef __MOD0_HPP
#define __MOD0_HPP

#include "common.hpp"
#include "gl.hpp"
#include "matrix.hpp"
#include "shader.hpp"

namespace {
  float const CUBE_VERTICES[] = {
    1.f,  1.f,  1.f,
    1.f, -1.f,  1.f,
    -1.f, -1.f,  1.f,
    -1.f,  1.f,  1.f,
    1.f,  1.f, -1.f,
    1.f, -1.f, -1.f,
    -1.f, -1.f, -1.f,
    -1.f,  1.f, -1.f
  };
  unsigned int const CUBE_INDICES[] = {
    /* front */
    0, 1, 2,
    0, 2, 3,
    /* back */
    4, 5, 6,
    4, 6, 7,
    /* left */
    2, 3, 6,
    3, 6, 7,
    /* right */
    0, 1, 4,
    1, 4, 5,
    /* top */
    0, 3, 4,
    3, 4, 7,
    /* back */
    1, 2, 5,
    2, 5, 6
  };
}

class mod0 {
  /* shader stuff */
  shader_c _stdVS;
  shader_c _stdGS;
  shader_c _stdFS;
  shader_c _ppFS;
  program_c _stdP;
  program_c _ppP;

  /* offscreen stuff */
  GLuint _offtex;
  GLuint _rdbf;
  GLuint _fbo;
  void _gen_offscreen_tex();
  void _gen_rdbf();
  void _gen_framebuffer();
  void _setup_offscreen();

  /* cube */
  GLuint _cubeBuffers[2];
  GLuint _cube;
  void _gen_buffers();
  void _gen_cube();

  /* projection */
  //mat4_c _perspective;

  /* uniform gates */
  GLuint _projIndex;
  GLuint _offtexIndex;
  GLuint _stdTimeIndex;
  GLuint _ppTimeIndex;
  void _init_uniforms();

public :
  mod0();
  ~mod0();
};

#endif /* guard */

