#include <cstdlib>
#include <iostream>
#include "common.hpp"
#include "matrix.hpp"
#include "mod1.hpp"

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
  _thunBlurFS(GL_FRAGMENT_SHADER) {
  /* tunnel setup */
  _tunFS.source(load_source(TUNNEL_FS_PATH).c_str());
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
  _thunVS.source(load_source(THUN_VS_PATH).c_str());
  _thunVS.compile();
  if (!_thunVS.compiled()) {
    cerr << "Thunder vertex shader failed to compile:\n" << _thunVS.compile_log() << endl;
    exit(1);
  }
  _thunTCS.source(load_source(THUN_TCS_PATH).c_str());
  _thunTCS.compile();
  if (!_thunTCS.compiled()) {
    cerr << "Thunder tessellation control shader failed to compile:\n" << _thunTCS.compile_log() << endl;
    exit(1);
  }
  _thunTES.source(load_source(THUN_TES_PATH).c_str());
  _thunTES.compile();
  if (!_thunTES.compiled()) {
    cerr << "Thunder tessellation evaluation shader failed to compile:\n" << _thunTES.compile_log() << endl;
    exit(1);
  }
  _thunFS.source(load_source(THUN_FS_PATH).c_str());
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
  _thunBlurFS.source(load_source(THUN_BLUR_FS_PATH).c_str());
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
  _init_uniforms();
  _init_thunders();
  _setup_offscreen();
}

mod1_c::~mod1_c() {
}

void mod1_c::_setup_offscreen() {
  /* prepare the offscreen texture */
  glGenTextures(2, _offtex);
  for (int i = 0; i < 2; ++i) {
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
  glGenFramebuffers(2, _fbo);
  for (int i = 0; i < 2; ++i) {
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
}

void mod1_c::render(float time) {
  /* tunnel render */
  glUseProgram(_tunP.id());
  glUniform1f(_tunTimeIndex, time);
  glRectf(-1.f, 1.f, 1.f, -1.f);

  /* thunders render */
  /* offscreen render */
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo[0]);
  glUseProgram(_thunP.id());
  glPatchParameteri(GL_PATCH_VERTICES, 2);
  glUniform1f(_thunTimeIndex, time);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindVertexArray(_thunders);
  glDrawArrays(GL_PATCHES, 0, THUNDERS_VERTICES_NB);
  glBindVertexArray(0);

  /* blur */
  glUseProgram(_thunBlurP.id());
  for (int i = 0, id = 0; i < BLUR_PASSES-1; ++i) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo[1 - id]);
    glBindTexture(GL_TEXTURE_2D, _offtex[id]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRectf(-1.f, 1.f, 1.f, -1.f);
    id = 1 - id;
  }

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, _offtex[BLUR_PASSES-1 & 1]);
  glClear(GL_DEPTH_BUFFER_BIT);
  glRectf(-1.f, 1.f, 1.f, -1.f);
}
