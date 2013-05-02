#include <cstdlib>
#include <iostream>
#include "common.hpp"
#include "matrix.hpp"
#include "mod1.hpp"

/* shaders sources */
#include "data/tunnel-fs.hpp"
#include "data/thun-vs.hpp"
#include "data/thun-tcs.hpp"
#include "data/thun-tes.hpp"
#include "data/thun-fs.hpp"
#include "data/thun-blur-fs.hpp"
#include "data/swap_lines-fs.hpp"

using namespace std;

namespace {
  int const THUNDERS_NB = 25;
  int const THUNDERS_VERTICES_NB = THUNDERS_NB*2; 
  int const BLUR_PASSES = 5;
}

mod1_c::mod1_c() :
  _tunFS(GL_FRAGMENT_SHADER),
  _thunVS(GL_VERTEX_SHADER),
  _thunTCS(GL_TESS_CONTROL_SHADER),
  _thunTES(GL_TESS_EVALUATION_SHADER),
  _thunGS(GL_GEOMETRY_SHADER),
  _thunFS(GL_FRAGMENT_SHADER),
  _thunBlurFS(GL_FRAGMENT_SHADER),
  _swapLinesFS(GL_FRAGMENT_SHADER) {
  /* tunnel setup */
#if 0
  _tunFS.source(load_source(TUNNEL_FS_PATH).c_str());
#endif
  _tunFS.source(SHD_TUNNEL_FS.c_str());
  _tunFS.compile();
  if (!_tunFS.compiled()) {
    cerr << "Tunnel fragment shader failed to compile:\n" << _tunFS.compile_log() << endl;
    exit(1);
  }
  _tunP.attach(_tunFS);
  _tunP.link();
  if (!_tunP.linked()) {
    cerr << "Tunnel shader program failed to link:\n" << _tunP.link_log() << endl;
    exit(2);
  }

  /* thunders field setup */
#if 0
  _thunVS.source(load_source(THUN_VS_PATH).c_str());
#endif
  _thunVS.source(SHD_THUN_VS.c_str());
  _thunVS.compile();
  if (!_thunVS.compiled()) {
    cerr << "Thunder vertex shader failed to compile:\n" << _thunVS.compile_log() << endl;
    exit(1);
  }
#if 0
  _thunTCS.source(load_source(THUN_TCS_PATH).c_str());
#endif
  _thunTCS.source(SHD_THUN_TCS.c_str());
  _thunTCS.compile();
  if (!_thunTCS.compiled()) {
    cerr << "Thunder tessellation control shader failed to compile:\n" << _thunTCS.compile_log() << endl;
    exit(1);
  }
#if 0
  _thunTES.source(load_source(THUN_TES_PATH).c_str());
#endif
  _thunTES.source(SHD_THUN_TES.c_str());
  _thunTES.compile();
  if (!_thunTES.compiled()) {
    cerr << "Thunder tessellation evaluation shader failed to compile:\n" << _thunTES.compile_log() << endl;
    exit(1);
  }
#if 0
  _thunFS.source(load_source(THUN_FS_PATH).c_str());
#endif
  _thunFS.source(SHD_THUN_FS.c_str());
  _thunFS.compile();
  if (!_thunFS.compiled()) {
    cerr << "Thunder fragment shader failed to compile:\n" << _thunFS.compile_log() << endl;
    exit(1);
  }
  _thunP.attach(_thunVS);
  _thunP.attach(_thunTCS);
  _thunP.attach(_thunTES);
  _thunP.attach(_thunFS);
  _thunP.link();
  if (!_thunP.linked()) {
    cerr << "Thunder program failed to link:\n" << _thunP.link_log() << endl;
    exit(2);
  }

  /* thunders blur */
#if 0
  _thunBlurFS.source(load_source(THUN_BLUR_FS_PATH).c_str());
#endif
  _thunBlurFS.source(SHD_THUN_BLUR_FS.c_str());
  _thunBlurFS.compile();
  if (!_thunBlurFS.compiled()) {
    cerr << "Thunder blur fragment shader failed to compile:\n" << _thunBlurFS.compile_log() << endl;
    exit(1);
  }
  _thunBlurP.attach(_thunBlurFS);
  _thunBlurP.link();
  if (!_thunBlurP.linked()) {
    cerr << "Thunder blur program failed to link:\n" << _thunBlurP.link_log() << endl;
    exit(2);
  }

  /* swap lines */
#if 0
  _swapLinesFS.source(load_source(SWAP_LINES_PATH_FS).c_str());
#endif
  _swapLinesFS.source(SHD_SWAP_LINES_FS.c_str());
  _swapLinesFS.compile();
  if (!_swapLinesFS.compiled()) {
    cerr << "Swap lines fragment shader failed to compile:\n" << _swapLinesFS.compile_log() << endl;
    exit(1);
  }
  _swapLinesP.attach(_swapLinesFS);
  _swapLinesP.link();
  if (!_swapLinesP.linked()) {
    cerr << "Swap lines program shader failed to link:\n" << _swapLinesP.link_log() << endl;
    exit(2);
  }

  _init_uniforms();
  _init_thunders();
  _setup_offscreen();
}

mod1_c::~mod1_c() {
}

void mod1_c::_setup_offscreen() {
  /* prepare the offscreen texture */
  glGenTextures(3, _offtex);
  for (int i = 0; i < 3; ++i) {
    glBindTexture(GL_TEXTURE_2D, _offtex[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, 0);
  }
  glBindTexture(GL_TEXTURE_2D, 0);

  /* prepare the renderbuffer */
  glGenRenderbuffers(1, &_rdbf);
  glBindRenderbuffer(GL_RENDERBUFFER, _rdbf);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  /* prepare the FBO */
  glGenFramebuffers(3, _fbo);
  for (int i = 0; i < 3; ++i) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo[i]);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rdbf);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _offtex[i], 0);

    auto ok = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    switch (ok) {
      case GL_FRAMEBUFFER_COMPLETE :
        cout << "framebuffer complete" << endl;
        break;

      default :
        cerr << "framebuffer incomplete" << endl;
    }
  }

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void mod1_c::_init_thunders() {
  glGenVertexArrays(1, &_thunders);
  glBindVertexArray(_thunders);
  glBindVertexArray(0);
}

void mod1_c::_init_uniforms() {
  /* tunnel uniforms init */
  GLint tunResIndex;

  glUseProgram(_tunP.id());
  _tunTimeIndex = _tunP.map_uniform("time");
  tunResIndex = _tunP.map_uniform("res");
  glUniform4f(tunResIndex, WIDTH, HEIGHT, IWIDTH, IHEIGHT);

  /* thunders field init */
  glUseProgram(_thunP.id());
  auto projIndex = _thunP.map_uniform("proj");
  auto p = gen_perspective(FOVY, RATIO, ZNEAR, ZFAR);

  glUniformMatrix4fv(projIndex, 1, GL_FALSE, p._);
  _thunTimeIndex = _thunP.map_uniform("time");

  /* thunders blur init */
  glUseProgram(_thunBlurP.id());
  auto texBlurIndex = _thunBlurP.map_uniform("offtex");
  auto thunBlurResIndex = _thunBlurP.map_uniform("res");
  glUniform4f(thunBlurResIndex, WIDTH, HEIGHT, IWIDTH, IHEIGHT);
  glUniform1i(texBlurIndex, 0);

  /* swap lines */
  glUseProgram(_swapLinesP.id());
  auto swapLinesRes = _swapLinesP.map_uniform("res");
  auto swapLinesOfftexIndex = _swapLinesP.map_uniform("offtex");
  _swapLinesTimeIndex = _swapLinesP.map_uniform("time");
  glUniform4f(swapLinesRes, WIDTH, HEIGHT, IWIDTH, IHEIGHT);
  glUniform1i(swapLinesOfftexIndex, 0);
}

void mod1_c::render(float time) {
  glEnable(GL_BLEND); /* maybe we'll need to place that in the bootstrap's initialization */
  glBlendFunc(GL_ONE, GL_ONE);

  /* tunnel render */
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo[2]);
  glUseProgram(_tunP.id());
  glUniform1f(_tunTimeIndex, time);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glRectf(-1.f, 1.f, 1.f, -1.f);

  /* thunders render */
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo[0]);
  glUseProgram(_thunP.id());
  glPatchParameteri(GL_PATCH_VERTICES, 2);
  glUniform1f(_thunTimeIndex, time);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindVertexArray(_thunders);
  glDrawArrays(GL_PATCHES, 0, THUNDERS_VERTICES_NB);
  glBindVertexArray(0);

  /* thuneders blur */
  glUseProgram(_thunBlurP.id());
  for (int i = 0, id = 0; i < BLUR_PASSES; ++i) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo[1 - id]);
    glBindTexture(GL_TEXTURE_2D, _offtex[id]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRectf(-1.f, 1.f, 1.f, -1.f);
    id = 1 - id;
  }

  /* combine blurred thunders to already rendered tunnel */
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo[2]);
  glBindTexture(GL_TEXTURE_2D, _offtex[(BLUR_PASSES-1) & 1]);
  glClear(GL_DEPTH_BUFFER_BIT);
  glRectf(-1.f, 1.f, 1.f, -1.f);

  /* swap lines */
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glUseProgram(_swapLinesP.id());
  glBindTexture(GL_TEXTURE_2D, _offtex[2]);
  glUniform1f(_swapLinesTimeIndex, time);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glRectf(-1.f, 1.f, 1.f, -1.f);
}
