#include "common.hpp"
#include "mod3.hpp"

using namespace std;

mod3_c::mod3_c() :
  _ppFS(GL_FRAGMENT_SHADER) {
  _ppFS.source(load_source(FINAL_FS_PATH).c_str());
  _ppFS.compile();
  if (!_ppFS.compiled()) {
    cerr << "Final fragment shader failed to compile:\n" << _ppFS.compile_log() << endl;
    exit(1);
  }
  _ppP.attach(_ppFS);
  _ppP.link();
  if (!_ppP.linked()) {
    cerr << "Final program shader failed to link:\n" << _ppP.link_log() << endl;
    exit(2);
  }

  _init_uniforms();
}

mod3_c::~mod3_c() {
}

void mod3_c::_init_uniforms() {
  _ppRes = _ppP.map_uniform("res");
  _ppTime = _ppP.map_uniform("time");
  glUseProgram(_ppP.id());
  glUniform4f(_ppRes, WIDTH, HEIGHT, IWIDTH, IHEIGHT);
}


void mod3_c::render(float time) {
  glUseProgram(_ppP.id());
  glUniform1f(_ppTime, time);
  glRectf(-1.f, 1.f, 1.f, -1.f);
}
