#include <iostream>
#include "common.hpp"
#include "mod2.hpp"

using namespace std;

mod2_c::mod2_c() :
  _stdVS(GL_VERTEX_SHADER),
  _stdFS(GL_FRAGMENT_SHADER) {
  _stdVS.source(load_source(STD_LAVA_VS_PATH).c_str());
  _stdVS.compile();
  if (!_stdVS.compiled()) {
    cerr << "STD Lava vertex shader failed to compile:\n" << _stdVS.compile_log() << endl;
    exit(1);
  }
  _stdFS.source(load_source(STD_LAVA_FS_PATH).c_str());
  _stdFS.compile();
  if (!_stdFS.compiled()) {
    cerr << "STD Lava fragment shader failed to compile:\n" << _stdFS.compile_log() << endl;
    exit(1);
  }
  _stdP.attach(_stdVS);
  _stdP.attach(_stdFS);
  _stdP.link();
  if (!_stdP.linked()) {
    cerr << "STD Lava shader program failed to link:\n" << _stdP.link_log() << endl;
    exit(2);
  }

  _init_uniforms();
}

mod2_c::~mod2_c() {
}

void mod2_c::_init_uniforms() {
  _stdTimeIndex = _stdP.map_uniform("time");
  _stdRes = _stdP.map_uniform("res");
  _stdFovy = _stdP.map_uniform("fovy");
  glUseProgram(_stdP.id());
  glUniform2f(_stdRes, WIDTH, HEIGHT);
  glUniform1f(_stdFovy, FOVY);
}

void mod2_c::render(float time) {
  glUseProgram(_stdP.id());
  glUniform1f(_stdTimeIndex, time);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glRectf(-1.f, 1.f, 1.f, -1.f);
}
