#include <iostream>
#include "common.hpp"
#include "mod1.hpp"

using namespace std;

mod1_c::mod1_c() :
  _tunFS(GL_FRAGMENT_SHADER),
  _thunVS(GL_VERTEX_SHADER),
  _thunTCS(GL_TESS_CONTROL_SHADER),
  _thunTES(GL_TESS_EVALUATION_SHADER),
  _thunGS(GL_GEOMETRY_SHADER),
  _thunFS(GL_FRAGMENT_SHADER) {
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
  _init_uniforms();
}

mod1_c::~mod1_c() {
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
  _thunTimeIndex = _thunP.map_uniform("time");
}

void mod1_c::render(float time) {
  /* tunnel render */
#if 0
  glUseProgram(_tunP.id());
  glUniform1f(_tunTimeIndex, time);
  glRectf(-1.f, 1.f, 1.f, -1.f);
#endif

  /* thunders render */
  glUseProgram(_thunP.id());
  glUniform1f(_thunTimeIndex, time);
  //glClear(GL_DEPTH_BUFFER_BIT);
  glRectf(-1.f, 1.f, 1.f, -1.f);
}
