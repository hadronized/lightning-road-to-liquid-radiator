#include <iostream>
#include "common.hpp"
#include "mod1.hpp"

using namespace std;

mod1_c::mod1_c() :
  _stdFS(GL_FRAGMENT_SHADER) {
  _stdFS.source(load_source(STD_TUNNEL_FS_PATH).c_str());
  _stdFS.compile();
  if (!_stdFS.compiled()) {
    cerr << "STD Tunnel fragment shader failed to compile:\n" << _stdFS.compile_log() << endl;
    exit(1);
  }
  _stdP.attach(_stdFS);
  _stdP.link();
  if (!_stdP.linked()) {
    cerr << "STD Tunnel shader program failed to link:\n" << _stdP.link_log() << endl;
    exit(2);
  }

  _init_uniforms();
}

mod1_c::~mod1_c() {
}

void mod1_c::_init_uniforms() {
  _stdTimeIndex = _stdP.map_uniform("time");
}

void mod1_c::render(float time) {
  glUseProgram(_stdP.id());
  glUniform1f(_stdTimeIndex, time);
  glRecf(-1.f, 1.f, 1.f, -1.f);
}
