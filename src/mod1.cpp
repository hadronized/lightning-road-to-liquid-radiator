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
#if 0
  _thunVS.source(load_source(THUN_VS_PATH).c_str());
  _thunVS.compile();
  if (!_thunVS.compiled()) {
    cerr << "Thunder vertex shader failed to compile:\n" << _thunVS.compile_log() << endl;
    exit(1);
  }
  _thunTCS.source(load_source(THUN_TCS_PATH).c_str());
  if (!_thunTCS.compiled()) {
    cerr << "Thunder tessellation control shader failed to compile:\n" << _thunTCS.compile_log() << endl;
    exit (1);
  }
  _thunTES.source(load_source(THUN_TES_PATH).c_str());
  _thunTES.compile();
  if (!_thunTES.compiled()) {
    cerr << "Thunder tessellation evaluation shader failed to compile:\n" << _thunTES.compile_log() << endl;
    exit (1);
  }
  _thunGS.source(load_source(THUN_GS_PATH).c_str());
  _thunGS.compile();
  if (!_thunGS.compiled()) {
    cerr << "Thunder geometry shader failed to compile:\n" << _thunGS.compile_log() << endl;
    exit (1);
  }
  _thunFS.source(load_source(THUN_FS_PATH).c_str());
  _thunFS.compile();
  if (!_thunFS.compiled()) {
    cerr << "Thunder fragment shader failed to compile:\n" << _thunFS.compile_log() << endl;
    exit (1);
  }
#endif

  _init_uniforms();
}

mod1_c::~mod1_c() {
}

void mod1_c::_init_uniforms() {
  _tunTimeIndex = _tunP.map_uniform("time");
  _tunRes = _tunP.map_uniform("res");
  _tunFovy = _tunP.map_uniform("fovy");
  glUseProgram(_tunP.id());
  glUniform2f(_tunRes, WIDTH, HEIGHT);
  glUniform1f(_tunFovy, FOVY);
}

void mod1_c::render(float time) {
  glUseProgram(_tunP.id());
  glUniform1f(_tunTimeIndex, time);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glRectf(-1.f, 1.f, 1.f, -1.f);
}
